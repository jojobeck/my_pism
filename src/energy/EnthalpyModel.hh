/* Copyright (C) 2016, 2017 PISM Authors
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

#ifndef ENTHALPYMODEL_H
#define ENTHALPYMODEL_H

#include "EnergyModel.hh"

namespace pism {
namespace energy {

/*! @brief The enthalpy-based energy balance model. */
class EnthalpyModel : public EnergyModel {
public:
  EnthalpyModel(IceGrid::ConstPtr grid, stressbalance::StressBalance *stress_balance);

protected:
  virtual void restart_impl(const PIO &input_file, int record);

  virtual void bootstrap_impl(const PIO &input_file,
                              const IceModelVec2S &ice_thickness,
                              const IceModelVec2S &surface_temperature,
                              const IceModelVec2S &climatic_mass_balance,
                              const IceModelVec2S &basal_heat_flux);

  virtual void initialize_impl(const IceModelVec2S &basal_melt_rate,
                               const IceModelVec2S &ice_thickness,
                               const IceModelVec2S &surface_temperature,
                               const IceModelVec2S &climatic_mass_balance,
                               const IceModelVec2S &basal_heat_flux);

  using EnergyModel::update_impl;
  virtual void update_impl(double t, double dt, const Inputs &inputs);

  virtual void define_model_state_impl(const PIO &output) const;
  virtual void write_model_state_impl(const PIO &output) const;
};

/*! @brief The "dummy" energy balance model. Reads in enthalpy from a file, but does not update it. */
class DummyEnergyModel : public EnthalpyModel {
public:
  DummyEnergyModel(IceGrid::ConstPtr grid, stressbalance::StressBalance *stress_balance);

protected:
  MaxTimestep max_timestep_impl(double t) const;

  void restart_impl(const PIO &input_file, int record);

  void bootstrap_impl(const PIO &input_file,
                      const IceModelVec2S &ice_thickness,
                      const IceModelVec2S &surface_temperature,
                      const IceModelVec2S &climatic_mass_balance,
                      const IceModelVec2S &basal_heat_flux);

  using EnergyModel::update_impl;
  void update_impl(double t, double dt, const Inputs &inputs);
};

} // end of namespace energy
} // end of namespace pism


#endif /* ENTHALPYMODEL_H */
