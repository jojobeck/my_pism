// Copyright (C) 2012, 2013, 2014, 2015, 2017 PISM Authors
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

#ifndef _PISMNC4FILE_H_
#define _PISMNC4FILE_H_

#include "NCFile.hh"

namespace pism {
namespace io {

class NC4File : public NCFile
{
public:
  NC4File(MPI_Comm com, unsigned int compression_level);
  virtual ~NC4File();

protected:
  // implementations:
  // open/create/close
  virtual int close_impl();

  // redef/enddef
  virtual int enddef_impl() const;

  virtual int redef_impl() const;

  // dim
  virtual int def_dim_impl(const std::string &name, size_t length) const;

  virtual int inq_dimid_impl(const std::string &dimension_name, bool &exists) const;

  virtual int inq_dimlen_impl(const std::string &dimension_name, unsigned int &result) const;

  virtual int inq_unlimdim_impl(std::string &result) const;

  virtual int inq_dimname_impl(int j, std::string &result) const;

  virtual int inq_ndims_impl(int &result) const;

  // var
  virtual int def_var_chunking_impl(const std::string &name,
                                    std::vector<size_t> &dimensions) const;

  virtual int def_var_impl(const std::string &name,
                           IO_Type nctype, const std::vector<std::string> &dims) const;

  virtual int get_vara_double_impl(const std::string &variable_name,
                                   const std::vector<unsigned int> &start,
                                   const std::vector<unsigned int> &count,
                                   double *ip) const;

  virtual int put_vara_double_impl(const std::string &variable_name,
                                   const std::vector<unsigned int> &start,
                                   const std::vector<unsigned int> &count,
                                   const double *op) const;

  virtual int get_varm_double_impl(const std::string &variable_name,
                                   const std::vector<unsigned int> &start,
                                   const std::vector<unsigned int> &count,
                                   const std::vector<unsigned int> &imap, double *ip) const;

  virtual int put_varm_double_impl(const std::string &variable_name,
                                   const std::vector<unsigned int> &start,
                                   const std::vector<unsigned int> &count,
                                   const std::vector<unsigned int> &imap, const double *op) const;

  virtual int inq_nvars_impl(int &result) const;

  virtual int inq_vardimid_impl(const std::string &variable_name, std::vector<std::string> &result) const;

  virtual int inq_varnatts_impl(const std::string &variable_name, int &result) const;

  virtual int inq_varid_impl(const std::string &variable_name, bool &exists) const;

  virtual int inq_varname_impl(unsigned int j, std::string &result) const;

  int inq_vartype_impl(const std::string &variable_name, IO_Type &result) const;

  // att
  virtual int get_att_double_impl(const std::string &variable_name, const std::string &att_name, std::vector<double> &result) const;

  virtual int get_att_text_impl(const std::string &variable_name, const std::string &att_name, std::string &result) const;

  using NCFile::put_att_double_impl;
  virtual int put_att_double_impl(const std::string &variable_name, const std::string &att_name, IO_Type xtype, const std::vector<double> &data) const;

  virtual int put_att_text_impl(const std::string &variable_name, const std::string &att_name, const std::string &value) const;

  virtual int inq_attname_impl(const std::string &variable_name, unsigned int n, std::string &result) const;

  virtual int inq_atttype_impl(const std::string &variable_name, const std::string &att_name, IO_Type &result) const;

  // misc
  virtual int set_fill_impl(int fillmode, int &old_modep) const;

  virtual std::string get_format_impl() const;
protected:
  virtual int set_access_mode(int varid, bool mapped) const;
  virtual int get_put_var_double(const std::string &variable_name,
                                 const std::vector<unsigned int> &start,
                                 const std::vector<unsigned int> &count,
                                 const std::vector<unsigned int> &imap, double *ip,
                                 bool get,
                                 bool mapped) const;
  unsigned int m_compression_level;
};

} // end of namespace io
} // end of namespace pism

#endif /* _PISMNC4FILE_H_ */
