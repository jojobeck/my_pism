// Copyright (C) 2013, 2014, 2015, 2016, 2017  David Maxwell and Constantine Khroulev
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

#ifndef IPGROUNDEDICEH1NORMFUNCTIONAL_HH_Q4IZKJOR
#define IPGROUNDEDICEH1NORMFUNCTIONAL_HH_Q4IZKJOR

#include "IPFunctional.hh"
#include "pism/util/Mask.hh"

namespace pism {

class IceModelVec2CellType;

namespace inverse {

//! Implements a functional corresponding to (the square of) an \f$H^1\f$ norm of a scalar valued function over a region with only grounded ice.
/*! The functional is, in continuous terms 
  \f[
  J(f) = \int_{\Omega_g} c_{H^1} \left|\nabla f\right|^2 + c_{L^2}f^2 \; dA
  \f]
  where \f$\Omega_g\f$ is a subset of the square domain consisting of grounded ice. 
  Numerically it is implemented using  Q1 finite elements.  Only those elements where all nodes
  have grounded ice are included in the integration, which alleviates edge effects due to steep
  derivatives in parameters that can occur at the transition between icy/non-icy regions.
  Integration can be 'restricted', in a sense, to a subset of the domain
  using a projection that forces \f$f\f$ to equal zero at nodes specified
  by the constructor argument \a dirichletLocations.
*/
class IPGroundedIceH1NormFunctional2S : public IPInnerProductFunctional<IceModelVec2S> {
public:
  IPGroundedIceH1NormFunctional2S(IceGrid::ConstPtr grid, double cL2, 
                                  double cH1, IceModelVec2CellType &ice_mask,
                                  IceModelVec2Int *dirichletLocations=NULL)
    : IPInnerProductFunctional<IceModelVec2S>(grid),
    m_cL2(cL2),
    m_cH1(cH1),
    m_dirichletIndices(dirichletLocations),
    m_ice_mask(ice_mask) {};
  virtual ~IPGroundedIceH1NormFunctional2S() {};
  
  virtual void valueAt(IceModelVec2S &x, double *OUTPUT);
  virtual void dot(IceModelVec2S &a, IceModelVec2S &b, double *OUTPUT);
  virtual void gradientAt(IceModelVec2S &x, IceModelVec2S &gradient);

  virtual void assemble_form(Mat J);

protected:

  double m_cL2, m_cH1;
  IceModelVec2Int *m_dirichletIndices;
  IceModelVec2CellType &m_ice_mask;

private:
  IPGroundedIceH1NormFunctional2S(IPGroundedIceH1NormFunctional2S const &);
  IPGroundedIceH1NormFunctional2S & operator=(IPGroundedIceH1NormFunctional2S const &);  
};

} // end of namespace inverse
} // end of namespace pism

#endif /* end of include guard: IPGROUNDEDICEH1NORMFUNCTIONAL_HH_Q4IZKJOR */
