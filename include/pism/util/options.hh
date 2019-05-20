/* Copyright (C) 2014, 2015 PISM Authors
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

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

namespace pism {
namespace options {

//! Template base class used by PISM's option-processing classes.
/*! (Ensures API consistency and helps code reuse.)
 */
template <typename T>
class Option {
public:
  Option() {
    m_is_set = false;
  }
  bool is_set() const {
    return m_is_set;
  }
  T value() const {
    return m_value;
  }
  operator T() const {
    return m_value;
  }
  const T* operator->() const {
    return &m_value;
  }
  T* operator->() {
    return &m_value;
  }
  bool operator==(const T& other) const {
    return m_value == other;
  }
protected:
  T    m_value;
  bool m_is_set;
  void set(T new_value, bool new_flag) {
    m_value  = new_value;
    m_is_set = new_flag;
  }
};

} // end of namespace options
} // end of namespace pism


#endif /* _OPTIONS_H_ */
