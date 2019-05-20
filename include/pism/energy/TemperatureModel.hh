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

#ifndef TEMPERATUREMODEL_H
#define TEMPERATUREMODEL_H

#include "EnergyModel.hh"

namespace pism {
namespace energy {

class TemperatureModel : public EnergyModel {
public:
  TemperatureModel(IceGrid::ConstPtr grid, stressbalance::StressBalance *stress_balance);

  const IceModelVec3 & temperature() const;

protected:
  void restart_impl(const PIO &input_file, int record);

  void bootstrap_impl(const PIO &input_file,
                      const IceModelVec2S &ice_thickness,
                      const IceModelVec2S &surface_temperature,
                      const IceModelVec2S &climatic_mass_balance,
                      const IceModelVec2S &basal_heat_flux);

  void initialize_impl(const IceModelVec2S &basal_melt_rate,
                       const IceModelVec2S &ice_thickness,
                       const IceModelVec2S &surface_temperature,
                       const IceModelVec2S &climatic_mass_balance,
                       const IceModelVec2S &basal_heat_flux);

  using EnergyModel::update_impl;
  void update_impl(double t, double dt, const Inputs &inputs);

  void define_model_state_impl(const PIO &output) const;
  void write_model_state_impl(const PIO &output) const;

  void column_drainage(const double rho, const double c, const double L,
                       const double z, const double dz,
                       double *Texcess, double *bwat) const;

  IceModelVec3 m_ice_temperature;
};

} // end of namespace energy
} // end of namespace pism

#endif /* TEMPERATUREMODEL_H */
