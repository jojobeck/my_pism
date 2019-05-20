/* Copyright (C) 2015, 2016 PISM Authors
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

#include "MaxTimestep.hh"

namespace pism {

// Time step restrictions
MaxTimestep::MaxTimestep()
  : m_finite(false), m_value(0.0) {
  // empty
}

MaxTimestep::MaxTimestep(double v)
  : m_finite(true), m_value(v) {
  // empty
}

MaxTimestep::MaxTimestep(const std::string &new_description)
  : m_finite(false), m_value(0.0), m_description(new_description) {
  // empty
}

MaxTimestep::MaxTimestep(double v, const std::string &new_description)
  : m_finite(true), m_value(v), m_description(new_description) {
  // empty
}

bool MaxTimestep::finite() const {
  return m_finite;
}

bool MaxTimestep::infinite() const {
  return not m_finite;
}

double MaxTimestep::value() const {
  return m_value;
}

std::string MaxTimestep::description() const {
  return m_description;
}

bool operator==(const MaxTimestep &a, const MaxTimestep &b) {
  if (a.finite() and b.finite()) {
    return a.value() == b.value();
  } else if (a.infinite() and b.infinite()) {
    return true;
  } else {
    return false;
  }
}

bool operator<(const MaxTimestep &a, const MaxTimestep &b) {
  if (a.finite() and b.finite()) {
    return a.value() < b.value();
  } else if (a.finite()) {
    return true;
  } else if (b.finite()) {
    return false;
  } else {
    return false;
  }
}

bool operator>(const MaxTimestep &a, const MaxTimestep &b) {
  return (not (a == b)) and (not (a < b));
}

} // end of namespace pism
