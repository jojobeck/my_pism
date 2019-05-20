/* Copyright (C) 2014, 2016 PISM Authors
 *
 * This file is part of PISM.
 *
 * PISM is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * PISM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PISM; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <vector>
#include <cstdlib>              // free

#include "ConfigJSON.hh"
#include "error_handling.hh"
#include "pism_utilities.hh"
#include "io/PIO.hh"

namespace pism {

/*! Given a 'path' "alice.bob.charlie", look for the JSON object 'bob'
 * containing a key 'charlie' in the object 'alice'. Use the 'object'
 * argument as the root.
 *
 * In other words, 'path' describes a node of a tree with 'object' as
 * the root, and this function returns the pointer to the node if
 * found, and NULL otherwise.
 */
static json_t* find_json_value(json_t *root, const std::string &name) {
  if (root == NULL) {
    return NULL;
  }

  json_t *object = root;
  for (auto object_name : split(name, '.')) {

    object = json_object_get(object, object_name.c_str());

    if (object == NULL) {
      break;
    }
  }

  return object;
}


template<typename PISMType, typename TMPType>
static void get_all_values(json_t *root, const std::string &path,
                           int type, const char *fmt, std::map<std::string,PISMType> &accum) {
  const char *key;
  json_t *value;

  json_object_foreach(root, key, value) {
    std::string parameter = path + key;
    int value_type = json_typeof(value);
    if (value_type == type) {
      TMPType tmp;
      if (json_unpack(value, fmt, &tmp) == 0) {
        accum[parameter] = tmp;
      } else {
        throw RuntimeError::formatted(PISM_ERROR_LOCATION, "failed to json_unpack %s using format %s",
                                      parameter.c_str(), fmt);
      }
    } else if (value_type == JSON_OBJECT) {
      get_all_values<PISMType, TMPType>(value, parameter + ".", type, fmt, accum);
    }
  }
}


template<typename PISMType, typename TMPType>
static PISMType get_value(json_t *object, const std::string &name,
                          const char *fmt, const char *type_name) {
  json_t *value = find_json_value(object, name);
  if (value == NULL) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "%s was not found", name.c_str());
  }

  TMPType tmp;
  if (json_unpack(value, fmt, &tmp) == 0) {
    return tmp;
  } else {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "failed to convert %s to a %s", name.c_str(), type_name);
  }
}

/*! Store a 'value' corresponding to the key 'name' in the database 'data'.
 *
 * If a name refers to an object "alice.bob", the object "alice" must
 * exist in the tree already, but "bob" may not exist before this call
 * and will be created. In other words, this method allows adding new
 * leaves only.
 */
static void set_value(json_t *data, const std::string &name, json_t *value) {
  std::vector<std::string> path = split(name, '.');
  if (path.size() == 0) {
    // stop if 'name' is empty
    return;
  }

  std::string key = path.back();
  path.pop_back();

  json_t *object = NULL;
  if (path.empty()) {
    object = data;
  } else {
    object = find_json_value(data, join(path, "."));
  }

  if (object != NULL) {
    if (json_is_object(object)) {
      json_object_set_new(object, key.c_str(), value);
    } else {
      throw RuntimeError::formatted(PISM_ERROR_LOCATION, "cannot set %s: %s is not an object",
                                    name.c_str(), join(path, ".").c_str());
    }
  } else {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "cannot set %s: %s is not found",
                                  name.c_str(), join(path, ".").c_str());
  }
}


ConfigJSON::ConfigJSON(units::System::Ptr unit_system)
  : Config(unit_system) {
  m_data = NULL;
  init_from_string("{}");
}

ConfigJSON::~ConfigJSON() {
  json_decref(m_data);
}

/*! Initialize the database by reading from a file 'filename'.
 */
void ConfigJSON::init_from_file(const std::string &filename) {

  // free existing data if present
  if (m_data != NULL) {
    json_decref(m_data);
  }

  json_error_t error;
  m_data = json_load_file(filename.c_str(), JSON_DECODE_INT_AS_REAL, &error);

  if (m_data == NULL) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "Error loading config from '%s'"
                                  " at line %d, column %d.",
                                  filename.c_str(), error.line, error.column);
  }
}

/*! Initialize the database using a string 'string'.
 */
void ConfigJSON::init_from_string(const std::string &string) {
  // free existing data if present
  if (m_data != NULL) {
    json_decref(m_data);
  }

  json_error_t error;
  m_data = json_loads(string.c_str(), JSON_DECODE_INT_AS_REAL, &error);

  if (m_data == NULL) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "Error loading config from '%s'"
                                  " at line %d, column %d.",
                                  string.c_str(), error.line, error.column);
  }
}

/*! Return the JSON string representation of the configuration database.
 */
std::string ConfigJSON::dump() const {
  std::string result;

  char *tmp = json_dumps(m_data, JSON_INDENT(2) | JSON_ENSURE_ASCII | JSON_SORT_KEYS);
  if (tmp != NULL) {
    result = tmp;
    free(tmp);
  }

  return result;
}

Config::Doubles ConfigJSON::all_doubles_impl() const {
  Config::Doubles result;
  get_all_values<double, double>(m_data, "", JSON_REAL, "F", result);
  return result;
}

Config::Strings ConfigJSON::all_strings_impl() const {
  Config::Strings result;
  get_all_values<std::string, const char*>(m_data, "", JSON_STRING, "s", result);
  return result;
}

Config::Booleans ConfigJSON::all_booleans_impl() const {
  Config::Booleans result;
  get_all_values<bool, int>(m_data, "", JSON_TRUE, "b", result);
  get_all_values<bool, int>(m_data, "", JSON_FALSE, "b", result);
  return result;
}

void ConfigJSON::set_double_impl(const std::string &name, double value) {
  set_value(m_data, name, json_pack("f", value));
}

void ConfigJSON::set_boolean_impl(const std::string &name, bool value) {
  set_value(m_data, name, json_pack("b", value));
}

void ConfigJSON::set_string_impl(const std::string &name, const std::string &value) {
  set_value(m_data, name, json_pack("s", value.c_str()));
}

double ConfigJSON::get_double_impl(const std::string &name) const {
  return get_value<double, double>(m_data, name, "F", "double");
}

std::string ConfigJSON::get_string_impl(const std::string &name) const {
  return get_value<std::string, const char *>(m_data, name, "s", "string");
}

bool ConfigJSON::get_boolean_impl(const std::string &name) const {
  return get_value<bool, int>(m_data, name, "b", "boolean");
}

void ConfigJSON::read_impl(const PIO &nc) {
  std::string config_string = nc.get_att_text("PISM_GLOBAL", "pism_config");
  this->init_from_string(config_string);
}

void ConfigJSON::write_impl(const PIO &nc) const {
  nc.put_att_text("PISM_GLOBAL", "pism_config", this->dump());
}

bool ConfigJSON::is_set_impl(const std::string &name) const {
  json_t *value = find_json_value(m_data, name);
  if (value == NULL) {
    return false;
  } else {
    return true;
  }
}

} // end of namespace pism
