#ifndef _PO_EXAMPLE_H_
#define _PO_EXAMPLE_H_

#include "coupler/PISMOcean.hh"
#include "base/util/iceModelVec2T.hh"

namespace pism {
namespace ocean {
//! \brief An example ocean model illustrating the use of `IceModelVec2T`.
class Example : public OceanModel {
public:
  Example(IceGrid::ConstPtr g);
  virtual ~Example();
protected:
  virtual MaxTimestep max_timestep_impl(double t) const;
  virtual void update_impl(double my_t, double my_dt);
  virtual void init_impl();
  virtual void sea_level_elevation_impl(double &result) const;
  virtual void shelf_base_temperature_impl(IceModelVec2S &result) const;
  virtual void shelf_base_mass_flux_impl(IceModelVec2S &result) const;
protected:
  IceModelVec2T m_shelf_melt_rate;
};

} // end of namespace ocean
} // end of namespace pism

#endif /* _PO_EXAMPLE_H_ */
