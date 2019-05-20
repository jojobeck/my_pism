// Copyright (C) 2009--2011, 2013, 2014, 2015, 2016, 2017 Constantine Khroulev
//
// This file is part of PISM.
//
// PISM is free software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or (at your option) any later
// version.
//
// PISM is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License
// along with PISM; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include <memory>
using std::dynamic_pointer_cast;

#include "Vars.hh"
#include "VariableMetadata.hh"
#include "iceModelVec.hh"
#include "IceModelVec2CellType.hh"
#include "error_handling.hh"

namespace pism {

Vars::Vars() {
}

bool Vars::is_available(const std::string &name) const {
  // check if "name" is a standard name
  if (m_standard_names.find(name) != m_standard_names.end()) {
    return true;
  }
  // check if "name" is a short name of a read-only variable
  if (m_variables.find(name) != m_variables.end()) {
    return true;
  }
  // check if "name" is a short name of a "shared" variable
  if (m_variables_shared.find(name) != m_variables_shared.end()) {
    return true;
  }
  return false;
}

//! \brief Add an IceModelVec v using the name `name`.
void Vars::add(const IceModelVec &v, const std::string &name) {

  if (m_variables.find(name) != m_variables.end()) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "Vars::add(): an IceModelVec with the name '%s'"
                                  " was added already.",
                                  name.c_str());
  }
  m_variables[name] = &v;
}

//!Add an IceModelVec to the dictionary.
/*!
  Adds standard_name if present, otherwise uses short_name.

  This code will only work for IceModelVecs with dof == 1.
*/
void Vars::add(const IceModelVec &v) {

  const SpatialVariableMetadata &m = v.metadata();
  std::string name = v.get_name();

  if (m.has_attribute("standard_name")) {

    std::string standard_name = m.get_string("standard_name");
    if (m_standard_names[standard_name].empty()) {
      m_standard_names[standard_name] = name;
    } else {
      throw RuntimeError::formatted(PISM_ERROR_LOCATION, "Vars::add(): an IceModelVec with the standard_name '%s'"
                                    " was added already.",
                                    standard_name.c_str());
    }
  }

  if (m_variables[name] == NULL) {
    m_variables[name] = &v;
  } else {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "Vars::add(): an IceModelVec with the name '%s'"
                                  " was added already.",
                                  name.c_str());
  }
}

//! Removes a variable with the key `name` from the dictionary.
void Vars::remove(const std::string &name) {

  const IceModelVec *v = m_variables[name];
  const SpatialVariableMetadata &m = v->metadata();

  if (v != NULL) {              // the argument is a "short" name
    m_variables.erase(name);
    if (m.has_attribute("standard_name")) {
      std::string std_name = m.get_string("standard_name");

      m_standard_names.erase(std_name);
    }
  } else {
    std::string &short_name = m_standard_names[name];
    v = m_variables[short_name];

    if (v != NULL) {            // the argument is a standard_name
      m_variables.erase(short_name);
      m_standard_names.erase(name);
    }
  }
}

//! \brief Returns a pointer to an IceModelVec containing variable `name` or
//! NULL if that variable was not found.
/*!
 * Checks standard_name first, then short name
 */
const IceModelVec* Vars::get(const std::string &name) const {
  const IceModelVec *tmp = get_internal(name);
  if (tmp == NULL) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "variable '%s' is not available", name.c_str());
  }
  return tmp;
}

const IceModelVec* Vars::get_internal(const std::string &name) const {

  auto j = m_standard_names.find(name);
  if (j != m_standard_names.end()) {
    std::string short_name = j->second;

    auto k = m_variables.find(short_name);
    if (k != m_variables.end()) {
      return k->second;
    }
  }

  auto k = m_variables.find(name);
  if (k != m_variables.end()) {
    return (k->second);
  }

  IceModelVec::Ptr shared = get_internal_shared(name);
  if ((bool)shared) {
    return shared.get();
  }

  return NULL;
}

const IceModelVec2S* Vars::get_2d_scalar(const std::string &name) const {
  const IceModelVec2S *tmp = dynamic_cast<const IceModelVec2S*>(this->get_internal(name));
  if (tmp == NULL) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "2D scalar variable '%s' is not available", name.c_str());
  }
  return tmp;
}

const IceModelVec2V* Vars::get_2d_vector(const std::string &name) const {
  const IceModelVec2V *tmp = dynamic_cast<const IceModelVec2V*>(this->get_internal(name));
  if (tmp == NULL) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "2D vector variable '%s' is not available", name.c_str());
  }
  return tmp;
}

const IceModelVec2Int* Vars::get_2d_mask(const std::string &name) const {
  const IceModelVec2Int *tmp = dynamic_cast<const IceModelVec2Int*>(this->get_internal(name));
  if (tmp == NULL) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "2D mask variable '%s' is not available", name.c_str());
  }
  return tmp;
}

const IceModelVec2CellType* Vars::get_2d_cell_type(const std::string &name) const {
  const IceModelVec2CellType *tmp = dynamic_cast<const IceModelVec2CellType*>(this->get_internal(name));
  if (tmp == NULL) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "2D cell type variable '%s' is not available", name.c_str());
  }
  return tmp;
}

const IceModelVec3* Vars::get_3d_scalar(const std::string &name) const {
  const IceModelVec3* tmp = dynamic_cast<const IceModelVec3*>(this->get_internal(name));
  if (tmp == NULL) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "3D scalar variable '%s' is not available", name.c_str());
  }
  return tmp;
}

//! \brief Returns the set of keys (variable names) in the dictionary.
/*!
 * Provides one (short) name per variable.
 *
 * This means that one can safely iterate over these keys, reading, writing,
 * displaying or de-allocating variables (without worrying that a variable will
 * get written or de-allocated twice).
 */
std::set<std::string> Vars::keys() const {

  std::set<std::string> result;

  for (auto v : m_variables) {
    result.insert(v.first);
  }

  for (auto v : m_variables_shared) {
    result.insert(v.first);
  }

  return result;
}

void Vars::add_shared(VecPtr variable) {

  const SpatialVariableMetadata &m = variable->metadata();
  std::string name = variable->get_name();

  if (m.has_attribute("standard_name")) {

    std::string standard_name = m.get_string("standard_name");
    if (m_standard_names[standard_name].empty()) {
      m_standard_names[standard_name] = name;
    } else {
      throw RuntimeError::formatted(PISM_ERROR_LOCATION, "Vars::add_shared(): an IceModelVec with the standard_name '%s'"
                                    " was added already.",
                                    standard_name.c_str());
    }
  }

  if (m_variables_shared.find(name) == m_variables_shared.end()) {
    m_variables_shared[name] = variable;
  } else {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "Vars::add_shared(): an IceModelVec with the name '%s'"
                                  " was added already.",
                                  name.c_str());
  }
}


void Vars::add_shared(VecPtr variable, const std::string &name) {

  if (m_variables_shared.find(name) != m_variables_shared.end()) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "Vars::add_shared(): an IceModelVec with the name '%s'"
                                  " was added already.",
                                  name.c_str());
  }
  m_variables_shared[name] = variable;
}


bool Vars::is_available_shared(const std::string &name) const {

  // check the standard name
  if (m_standard_names.find(name) != m_standard_names.end()) {
    std::string short_name = m_standard_names[name];
    // return true if the corresponding short name is one of a
    // "shared" variable
    if (m_variables_shared.find(short_name) != m_variables_shared.end()) {
      return true;
    }
    return false;
  }

  // check if "name" is a short name of a "shared" variable
  if (m_variables_shared.find(name) != m_variables_shared.end()) {
    return true;
  }
  return false;
}


IceModelVec::Ptr Vars::get_shared(const std::string &name) const {
  IceModelVec::Ptr tmp = get_internal_shared(name);
  if (not (bool)tmp) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "shared variable '%s' is not available", name.c_str());
  }
  return tmp;
}


IceModelVec2S::Ptr Vars::get_2d_scalar_shared(const std::string &name) const {
  IceModelVec2S::Ptr tmp = dynamic_pointer_cast<IceModelVec2S,IceModelVec>(this->get_internal_shared(name));
  if (not (bool)tmp) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "shared 2D scalar variable '%s' is not available", name.c_str());
  }
  return tmp;
}


IceModelVec2V::Ptr Vars::get_2d_vector_shared(const std::string &name) const {
  IceModelVec2V::Ptr tmp = dynamic_pointer_cast<IceModelVec2V,IceModelVec>(this->get_internal_shared(name));
  if (not (bool)tmp) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "shared 2D vector variable '%s' is not available", name.c_str());
  }
  return tmp;
}


IceModelVec2Int::Ptr Vars::get_2d_mask_shared(const std::string &name) const {
  IceModelVec2Int::Ptr tmp = dynamic_pointer_cast<IceModelVec2Int,IceModelVec>(this->get_internal_shared(name));
  if (not (bool)tmp) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "shared 2D mask variable '%s' is not available", name.c_str());
  }
  return tmp;
}

IceModelVec2CellType::Ptr Vars::get_2d_cell_type_shared(const std::string &name) const {
  IceModelVec2CellType::Ptr tmp = dynamic_pointer_cast<IceModelVec2CellType,IceModelVec>(this->get_internal_shared(name));
  if (not (bool)tmp) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "shared 2D mask variable '%s' is not available", name.c_str());
  }
  return tmp;
}


IceModelVec3::Ptr Vars::get_3d_scalar_shared(const std::string &name) const {
  IceModelVec3::Ptr tmp = dynamic_pointer_cast<IceModelVec3,IceModelVec>(this->get_internal_shared(name));
  if (not (bool)tmp) {
    throw RuntimeError::formatted(PISM_ERROR_LOCATION, "shared 3D scalar variable '%s' is not available", name.c_str());
  }
  return tmp;
}


std::set<std::string> Vars::keys_shared() const {

  std::set<std::string> result;
  for (auto v : m_variables_shared) {
    result.insert(v.first);
  }

  return result;
}

IceModelVec::Ptr Vars::get_internal_shared(const std::string &name) const {

  auto j = m_standard_names.find(name);
  if (j != m_standard_names.end()) {
    std::string short_name = j->second;

    auto k = m_variables_shared.find(short_name);
    if (k != m_variables_shared.end()) {
      return k->second;
    } else {
      return IceModelVec::Ptr();
    }
  }

  auto k = m_variables_shared.find(name);
  if (k != m_variables_shared.end()) {
    return (k->second);
  }

  return IceModelVec::Ptr();
}

} // end of namespace pism
