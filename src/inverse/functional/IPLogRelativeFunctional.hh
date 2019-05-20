// Copyright (C) 2013, 2014, 2015  David Maxwell and Constantine Khroulev
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

#ifndef IPLOGRELATIVEFUNCTIONAL_HH_97I6BWHG
#define IPLOGRELATIVEFUNCTIONAL_HH_97I6BWHG

#include "IPFunctional.hh"

namespace pism {
namespace inverse {

//! Implements a functional for log-relative errors.
/*!  Specifically, given a reference function \f$u_{obs}=[U_i]\f$,
  \f[
  J(x) = c_N \sum_i \log\left(1+W_i\frac{|X_i|^2}{|U_{i}|^2+\epsilon^2}\right)
  \f]
  where \f$\epsilon={\tt inv_ssa_velocity_eps}\f$ and \f$w\f$ is an optionally
  provided weight function.  The normalization constant \f$c_N\f$ is determined 
  implicitly by normalize().
*/
class IPLogRelativeFunctional : public IPFunctional<IceModelVec2V> {
public:
  IPLogRelativeFunctional(IceGrid::ConstPtr grid, IceModelVec2V &u_observed, double eps,
                          IceModelVec2S *weights=NULL) :
    IPFunctional<IceModelVec2V>(grid), m_u_observed(u_observed), m_weights(weights), m_normalization(1.), m_eps(eps) {};
  virtual ~IPLogRelativeFunctional() {};

  virtual void normalize(double scale);

  virtual void valueAt(IceModelVec2V &x, double *OUTPUT);
  virtual void gradientAt(IceModelVec2V &x, IceModelVec2V &gradient);

protected:
  IceModelVec2V &m_u_observed;
  IceModelVec2S *m_weights;
  double m_normalization;
  double m_eps;
};


} // end of namespace inverse
} // end of namespace pism

#endif /* end of include guard: IPLOGRELATIVEFUNCTIONAL_HH_97I6BWHG */
