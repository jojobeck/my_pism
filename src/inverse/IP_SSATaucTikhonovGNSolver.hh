// Copyright (C) 2012, 2014, 2015, 2016, 2017  David Maxwell
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

#ifndef IP_SSATAUCTIKHONOVGN_HH_SIU7F33G
#define IP_SSATAUCTIKHONOVGN_HH_SIU7F33G

#include "IP_SSATaucForwardProblem.hh"
#include "pism/util/TerminationReason.hh"
#include "pism/util/error_handling.hh"
#include "pism/util/iceModelVec.hh"
#include "pism/util/petscwrappers/KSP.hh"
#include "functional/IPFunctional.hh"

namespace pism {
namespace inverse {

template<class C, void (C::*MultiplyCallback)(Vec,Vec) >
class MatrixMultiplyCallback {
public:
  static void connect(Mat A) {
    PetscErrorCode ierr;
    ierr = MatShellSetOperation(A, MATOP_MULT,
                                (void(*)(void))MatrixMultiplyCallback::callback);
    PISM_CHK(ierr, "MatShellSetOperation");
  }
protected:
  static PetscErrorCode callback(Mat A, Vec x, Vec y) {
    try {
      C *ctx;
      PetscErrorCode ierr = MatShellGetContext(A,&ctx);
      PISM_CHK(ierr, "MatShellGetContext");
      (ctx->*MultiplyCallback)(x,y);
    } catch (...) {
      MPI_Comm com = MPI_COMM_SELF;
      PetscErrorCode ierr = PetscObjectGetComm((PetscObject)A, &com); CHKERRQ(ierr);
      handle_fatal_errors(com);
      SETERRQ(com, 1, "A PISM callback failed");
    }
    return 0;
  }
};

class IP_SSATaucTikhonovGNSolver {
public:
  typedef IceModelVec2S DesignVec;
  typedef IceModelVec2V StateVec;
  // typedef IP_SSATaucTikhonovGNSolverListener Listener;

  IP_SSATaucTikhonovGNSolver(IP_SSATaucForwardProblem &ssaforward, DesignVec &d0, StateVec &u_obs, double eta, 
                              IPInnerProductFunctional<DesignVec> &designFunctional, IPInnerProductFunctional<StateVec> &stateFunctional);

  ~IP_SSATaucTikhonovGNSolver();
  
  virtual StateVec::Ptr stateSolution() {
    return m_ssaforward.solution();
  }

  virtual DesignVec::Ptr designSolution() {
    return m_d;
  }

  virtual void setInitialGuess(DesignVec &d) {
    m_d->copy_from(d);
  }

  //! Sets the desired target misfit (in units of \f$\sqrt{J_{\rm misfit}}\f$).
  virtual void setTargetMisfit(double misfit) {
    m_target_misfit = misfit;
  }

  virtual void evaluateGNFunctional(DesignVec &h, double *value);

  virtual void apply_GN(IceModelVec2S &h, IceModelVec2S &out);
  virtual void apply_GN(Vec h, Vec out);

  virtual TerminationReason::Ptr init();

  virtual TerminationReason::Ptr check_convergence(); 
  
  virtual TerminationReason::Ptr solve();

  virtual TerminationReason::Ptr evaluate_objective_and_gradient();

protected:

  virtual void assemble_GN_rhs(DesignVec &out);

  virtual TerminationReason::Ptr solve_linearized();

  virtual TerminationReason::Ptr compute_dlogalpha(double *dalpha);

  virtual TerminationReason::Ptr linesearch();

  IP_SSATaucForwardProblem &m_ssaforward;

  DesignVec m_x;
  DesignVec m_y;

  DesignVec m_tmp_D1Global;
  DesignVec m_tmp_D2Global;
  DesignVec m_tmp_D1Local;
  DesignVec m_tmp_D2Local;
  StateVec  m_tmp_S1Global;
  StateVec  m_tmp_S2Global;
  StateVec  m_tmp_S1Local;
  StateVec  m_tmp_S2Local;

  DesignVec  m_GN_rhs;

  DesignVec::Ptr m_d;
  DesignVec &m_d0;
  DesignVec m_dGlobal;
  DesignVec m_d_diff;
  DesignVec m_d_diff_lin;

  DesignVec m_h;
  DesignVec m_hGlobal;
  DesignVec m_dalpha_rhs;
  DesignVec m_dh_dalpha;
  DesignVec m_dh_dalphaGlobal;

  DesignVec m_grad_design;
  DesignVec m_grad_state;
  DesignVec m_gradient;
  
  double m_val_design, m_val_state, m_value;

  StateVec &m_u_obs;
  StateVec m_u_diff;

  petsc::KSP m_ksp;  
  petsc::Mat m_mat_GN;

  double m_eta;
  IPInnerProductFunctional<DesignVec> &m_designFunctional;
  IPInnerProductFunctional<StateVec> &m_stateFunctional;

  double m_alpha;
  double m_logalpha;
  double m_target_misfit;

  int m_iter, m_iter_max;
  bool m_tikhonov_adaptive;
  double m_vel_scale;
  double m_tikhonov_rtol, m_tikhonov_atol, m_tikhonov_ptol;

  MPI_Comm m_comm;
  Logger::ConstPtr m_log;
};

} // end of namespace inverse
} // end of namespace pism

#endif /* end of include guard: IP_SSATAUCTIKHONOVGN_HH_SIU7F33G */
