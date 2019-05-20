// Copyright (C) 2012, 2013, 2014, 2015, 2016, 2017 PISM Authors
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

#ifndef _PISMNCWRAPPER_H_
#define _PISMNCWRAPPER_H_

#include <memory>
#include <string>
#include <vector>

#include <mpi.h>

#include "IO_Flags.hh"

namespace pism {

class ErrorLocation;

//! Input and output code (NetCDF wrappers, etc)
namespace io {

//! \brief The PISM wrapper for a subset of the NetCDF C API.
/*!
 * The goal of this class is to hide the fact that we need to communicate data
 * to and from the processor zero. Using this wrapper we should be able to
 * write code that looks good and works both on 1-processor and
 * multi-processor systems.
 *
 * Moreover, this way we can switch underlying I/O implementations.
 *
 * Notes:
 * - It uses C++ STL strings instead of C character arrays
 * - It hides NetCDF ncid, dimid and varid and uses strings to reference
 *   dimensions and variables instead.
 * - This class does not and should not use any PETSc API calls.
 * - This wrapper provides access to a very small portion of the NetCDF C API.
 *   (Only calls used in PISM.) This is intentional.
 * - Methods of this class should do what corresponding NetCDF C API calls do,
 *   no more and no less.
 */
class NCFile
{
public:
  typedef std::shared_ptr<NCFile> Ptr;

  NCFile(MPI_Comm com);
  virtual ~NCFile();

  // open/create/close
  void open(const std::string &filename, IO_Mode mode);

  void create(const std::string &filename);

  void close();

  // redef/enddef
  void enddef() const;

  void redef() const;

  // dim
  void def_dim(const std::string &name, size_t length) const;

  void inq_dimid(const std::string &dimension_name, bool &exists) const;

  void inq_dimlen(const std::string &dimension_name, unsigned int &result) const;

  void inq_unlimdim(std::string &result) const;

  void inq_dimname(int j, std::string &result) const;

  void inq_ndims(int &result) const;

  // var
  void def_var(const std::string &name, IO_Type nctype,
               const std::vector<std::string> &dims) const;

  void def_var_chunking(const std::string &name, std::vector<size_t> &dimensions) const;

  void get_vara_double(const std::string &variable_name,
                       const std::vector<unsigned int> &start,
                       const std::vector<unsigned int> &count,
                       double *ip) const;

  void put_vara_double(const std::string &variable_name,
                       const std::vector<unsigned int> &start,
                       const std::vector<unsigned int> &count,
                       const double *op) const;

  void get_varm_double(const std::string &variable_name,
                       const std::vector<unsigned int> &start,
                       const std::vector<unsigned int> &count,
                       const std::vector<unsigned int> &imap,
                       double *ip) const;

  void put_varm_double(const std::string &variable_name,
                       const std::vector<unsigned int> &start,
                       const std::vector<unsigned int> &count,
                       const std::vector<unsigned int> &imap,
                       const double *op) const;

  void inq_nvars(int &result) const;

  void inq_vardimid(const std::string &variable_name, std::vector<std::string> &result) const;

  void inq_varnatts(const std::string &variable_name, int &result) const;

  void inq_varid(const std::string &variable_name, bool &exists) const;

  void inq_varname(unsigned int j, std::string &result) const;

  void inq_vartype(const std::string &variable_name, IO_Type &result) const;

  // att
  void get_att_double(const std::string &variable_name, const std::string &att_name,
                      std::vector<double> &result) const;

  void get_att_text(const std::string &variable_name, const std::string &att_name,
                    std::string &result) const;

  void put_att_double(const std::string &variable_name, const std::string &att_name,
                      IO_Type xtype, const std::vector<double> &data) const;

  void put_att_double(const std::string &variable_name, const std::string &att_name,
                      IO_Type xtype, double value) const;

  void put_att_text(const std::string &variable_name, const std::string &att_name,
                    const std::string &value) const;

  void inq_attname(const std::string &variable_name, unsigned int n, std::string &result) const;

  void inq_atttype(const std::string &variable_name, const std::string &att_name, IO_Type &result) const;

  // misc
  void set_fill(int fillmode, int &old_modep) const;

  std::string get_filename() const;

  std::string get_format() const;

  void move_if_exists(const std::string &filename, int rank_to_use = 0);
  void remove_if_exists(const std::string &filename, int rank_to_use = 0);

protected:
  // implementations:

  // open/create/close
  virtual int open_impl(const std::string &filename, IO_Mode mode) = 0;
  virtual int create_impl(const std::string &filename) = 0;
  virtual int close_impl() = 0;

  // redef/enddef
  virtual int enddef_impl() const = 0;

  virtual int redef_impl() const = 0;

  // dim
  virtual int def_dim_impl(const std::string &name, size_t length) const = 0;

  virtual int inq_dimid_impl(const std::string &dimension_name, bool &exists) const = 0;

  virtual int inq_dimlen_impl(const std::string &dimension_name, unsigned int &result) const = 0;

  virtual int inq_unlimdim_impl(std::string &result) const = 0;

  virtual int inq_dimname_impl(int j, std::string &result) const = 0;

  virtual int inq_ndims_impl(int &result) const = 0;

  // var
  virtual int def_var_impl(const std::string &name, IO_Type nctype,
                           const std::vector<std::string> &dims) const = 0;

  virtual int def_var_chunking_impl(const std::string &name,
                                    std::vector<size_t> &dimensions) const;

  virtual int get_vara_double_impl(const std::string &variable_name,
                                   const std::vector<unsigned int> &start,
                                   const std::vector<unsigned int> &count,
                                   double *ip) const = 0;

  virtual int put_vara_double_impl(const std::string &variable_name,
                                   const std::vector<unsigned int> &start,
                                   const std::vector<unsigned int> &count,
                                   const double *op) const = 0;

  virtual int get_varm_double_impl(const std::string &variable_name,
                                   const std::vector<unsigned int> &start,
                                   const std::vector<unsigned int> &count,
                                   const std::vector<unsigned int> &imap,
                                   double *ip) const = 0;

  virtual int put_varm_double_impl(const std::string &variable_name,
                                   const std::vector<unsigned int> &start,
                                   const std::vector<unsigned int> &count,
                                   const std::vector<unsigned int> &imap,
                                   const double *op) const = 0;

  virtual int inq_nvars_impl(int &result) const = 0;

  virtual int inq_vardimid_impl(const std::string &variable_name, std::vector<std::string> &result) const = 0;

  virtual int inq_varnatts_impl(const std::string &variable_name, int &result) const = 0;

  virtual int inq_varid_impl(const std::string &variable_name, bool &exists) const = 0;

  virtual int inq_varname_impl(unsigned int j, std::string &result) const = 0;

  virtual int inq_vartype_impl(const std::string &variable_name, IO_Type &result) const = 0;

  // att
  virtual int get_att_double_impl(const std::string &variable_name, const std::string &att_name, std::vector<double> &result) const = 0;

  virtual int get_att_text_impl(const std::string &variable_name, const std::string &att_name, std::string &result) const = 0;

  virtual int put_att_double_impl(const std::string &variable_name, const std::string &att_name, IO_Type xtype, const std::vector<double> &data) const = 0;

  virtual int put_att_double_impl(const std::string &variable_name, const std::string &att_name, IO_Type xtype, double value) const;

  virtual int put_att_text_impl(const std::string &variable_name, const std::string &att_name, const std::string &value) const = 0;

  virtual int inq_attname_impl(const std::string &variable_name, unsigned int n, std::string &result) const = 0;

  virtual int inq_atttype_impl(const std::string &variable_name, const std::string &att_name, IO_Type &result) const = 0;

  // misc
  virtual int set_fill_impl(int fillmode, int &old_modep) const = 0;

  virtual std::string get_format_impl() const = 0;

  virtual int move_if_exists_impl(const std::string &filename, int rank_to_use = 0);
  virtual int remove_if_exists_impl(const std::string &filename, int rank_to_use = 0);

  virtual int integer_open_mode(IO_Mode input) const = 0;

  std::string get_filename_impl() const;

protected:
  // internal:
  virtual void check(const ErrorLocation &where, int return_code) const;

protected:                      // data members

  MPI_Comm m_com;
  int m_file_id;
  std::string m_filename;
  mutable bool m_define_mode;
  // negative values of m_[xy][ms] mean "not initialized"
  mutable int m_xs, m_xm, m_ys, m_ym;
};

} // end of namespace io
} // end of namespace pism

#endif /* _PISMNCWRAPPER_H_ */
