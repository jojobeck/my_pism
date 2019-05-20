/* Copyright (C) 2016, 2017, 2018 PISM Authors
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

#ifndef VONMISESCALVING_H
#define VONMISESCALVING_H

#include "StressCalving.hh"

namespace pism {

class IceModelVec2S;

namespace rheology {
class FlowLaw;
} // end of namespace rheology

namespace calving {

class vonMisesCalving : public StressCalving {
public:
  vonMisesCalving(IceGrid::ConstPtr grid, std::shared_ptr<const rheology::FlowLaw> flow_law);
  virtual ~vonMisesCalving();

  void init();

protected:
  virtual DiagnosticList diagnostics_impl() const;

  void compute_calving_rate(const CalvingInputs &inputs,
                            IceModelVec2S &result) const;

  std::shared_ptr<const rheology::FlowLaw> m_flow_law;
};

} // end of namespace calving
} // end of namespace pism

#endif /* VONMISESCALVING_H */
