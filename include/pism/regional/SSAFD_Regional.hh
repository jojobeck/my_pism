/* Copyright (C) 2015, 2016, 2017 PISM Authors
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

#ifndef _SSAFD_REGIONAL_H_
#define _SSAFD_REGIONAL_H_

#include "pism/stressbalance/ssa/SSAFD.hh"

namespace pism {

namespace stressbalance {

//! \brief A version of the SSA stress balance with tweaks for outlet glacier
//! simulations.
class SSAFD_Regional : public SSAFD {
public:
  SSAFD_Regional(IceGrid::ConstPtr g);
  virtual ~SSAFD_Regional();
  virtual void init();
  virtual void compute_driving_stress(const Geometry &geometry, IceModelVec2V &result) const;

private:
  void update(const Inputs &inputs, bool full_update);

  const IceModelVec2S   *m_h_stored;
  const IceModelVec2S   *m_H_stored;
  const IceModelVec2Int *m_no_model_mask;
};

} // end of namespace stressbalance

} // end of namespace pism

#endif /* _SSAFD_REGIONAL_H_ */
