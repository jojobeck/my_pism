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

#include "EnthalpyModel_Regional.hh"

namespace pism {
namespace energy {

EnthalpyModel_Regional::EnthalpyModel_Regional(IceGrid::ConstPtr grid,
                                               stressbalance::StressBalance *stress_balance)
  : EnthalpyModel(grid, stress_balance) {
  // Note that the name of this variable (bmr_stored) does not matter: it is
  // *never* read or written. We make a copy of basal_melt_rate_grounded instead.
  m_basal_melt_rate_stored.create(m_grid, "bmr_stored", WITHOUT_GHOSTS);
  m_basal_melt_rate_stored.set_attrs("internal",
                                     "time-independent basal melt rate in the no-model-strip",
                                     "m s-1", "");
}

void EnthalpyModel_Regional::restart_impl(const PIO &input_file, int record) {
  EnthalpyModel::restart_impl(input_file, record);

  m_basal_melt_rate_stored.copy_from(m_basal_melt_rate);
}

void EnthalpyModel_Regional::bootstrap_impl(const PIO &input_file,
                                            const IceModelVec2S &ice_thickness,
                                            const IceModelVec2S &surface_temperature,
                                            const IceModelVec2S &climatic_mass_balance,
                                            const IceModelVec2S &basal_heat_flux) {

  EnthalpyModel::bootstrap_impl(input_file, ice_thickness, surface_temperature,
                               climatic_mass_balance, basal_heat_flux);

  m_basal_melt_rate_stored.copy_from(m_basal_melt_rate);
}

void EnthalpyModel_Regional::initialize_impl(const IceModelVec2S &basal_melt_rate,
                                             const IceModelVec2S &ice_thickness,
                                             const IceModelVec2S &surface_temperature,
                                             const IceModelVec2S &climatic_mass_balance,
                                             const IceModelVec2S &basal_heat_flux) {

  EnthalpyModel::initialize_impl(basal_melt_rate,
                                 ice_thickness,
                                 surface_temperature,
                                 climatic_mass_balance,
                                 basal_heat_flux);

  m_basal_melt_rate_stored.copy_from(m_basal_melt_rate);
}


void EnthalpyModel_Regional::update_impl(double t, double dt,
                                         const Inputs &inputs) {

  unsigned int Mz = m_grid->Mz();

  EnthalpyModel::update_impl(t, dt, inputs);

  const IceModelVec2Int &no_model_mask = *inputs.no_model_mask;

  // The update_impl() call above sets m_work; ghosts are communicated
  // later (in EnergyModel::update()).
  IceModelVec::AccessList list{&no_model_mask, &m_work, &m_ice_enthalpy,
      &m_basal_melt_rate, &m_basal_melt_rate_stored};

  for (Points p(*m_grid); p; p.next()) {
    const int i = p.i(), j = p.j();

    if (no_model_mask(i, j) > 0.5) {
      double *new_enthalpy = m_work.get_column(i, j);
      double *old_enthalpy = m_ice_enthalpy.get_column(i, j);

      // enthalpy
      for (unsigned int k = 0; k < Mz; ++k) {
        new_enthalpy[k] = old_enthalpy[k];
      }

      // basal melt rate
      m_basal_melt_rate(i, j) = m_basal_melt_rate_stored(i, j);
    }
  }
}

} // end of namespace energy
} // end of namespace pism
