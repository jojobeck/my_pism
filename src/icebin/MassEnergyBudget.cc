#include <iostream>
#include <pism/icebin/MassEnergyBudget.hh>
#include <pism/util/error_handling.hh>

namespace pism{
namespace icebin{


void MassEnthVec2S::create(pism::IceGrid::ConstPtr my_grid, const std::string &my_name,
	pism::IceModelVecKind ghostedp, int width)
{
	mass.create(my_grid, my_name + ".mass", ghostedp, width);
	enth.create(my_grid, my_name + ".enth", ghostedp, width);
}

void MassEnthVec2S::set_attrs(
	const std::string &my_pism_intent,
	const std::string &my_long_name,
	const std::string &my_units,
	const std::string &my_standard_name)
{
	mass.set_attrs(my_pism_intent, my_long_name + " (mass portion)",
		"kg " + my_units, my_standard_name + ".mass", 0);
	enth.set_attrs(my_pism_intent, my_long_name + " (enthalpy portion)",
		"J " + my_units, my_standard_name + ".enth", 0);
}

MassEnergyBudget::MassEnergyBudget()
{
}

void MassEnergyBudget::create(pism::IceGrid::ConstPtr grid, std::string const &prefix,
	pism::IceModelVecKind ghostedp, unsigned int width)
{
        if (all_vecs.size() != 0) throw RuntimeError(PISM_ERROR_LOCATION,
        "MassEnergyBudget::create() cannot be called twice, fix your code!");
	printf("MassEnergyBudget(%p)::create()\n", (void*)this);

	// ----------- Mass and Enthalpy State of the Ice Sheet
	total.create(grid, prefix+"total",
		ghostedp, width);
	total.set_attrs("diagnostic",
		"State of the ice sheet (NOT a difference between timetseps)",
		"m-2", "total");
	add_massenth(total, TOTAL, "", "");

	// ----------- Heat generation of flows [vertical]
	// Postive means heat is flowing INTO the ice sheet.
	basal_frictional_heating.create(grid, prefix+"basal_frictional_heating",
		ghostedp, width);
	basal_frictional_heating.set_attrs("internal",
		"Basal frictional heating",
		"W m-2", "");
	add_enth(basal_frictional_heating, DELTA, "basal_frictional_heating");

	strain_heating.create(grid, prefix+"strain_heating",
		ghostedp, width);
	strain_heating.set_attrs("internal",
		"Strain heating",
		"W m-2", "");
	add_enth(strain_heating, DELTA, "strain_heating");	//!< Total amount of strain heating [J/m^2]

	geothermal_flux.create(grid, prefix+"geothermal_flux",
		ghostedp, width);
	geothermal_flux.set_attrs("internal",
		"Geothermal energy through (compare to upward_geothermal_flux?)",
		"W m-2", "");
	add_enth(geothermal_flux, 0, "geothermal_flux");	//!< Total amount of geothermal energy [J/m^2]

	upward_geothermal_flux.create(grid, prefix+"upward_geothermal_flux",
		ghostedp, width);
	upward_geothermal_flux.set_attrs("internal",
		"Geothermal energy through (compare to geothermal_flux?)",
		"W m-2", "");
	add_enth(upward_geothermal_flux, DELTA, "upward_geothermal_flux");	//!< Total amount of geothermal energy [J/m^2]

	// ----------- Mass advection, with accompanying enthalpy change
	// Postive means mass/enthalpy is flowing INTO the ice sheet.
	std::string name;

	calving.create(grid, prefix+"calving",
		ghostedp, width);
	calving.set_attrs("diagnostic",
		"Mass/Enthalpy gain from calving.  Should be negative.",
		"m-2 s-1", "calving");
	add_massenth(calving, DELTA, "calving.mass", "calving.enth");

	pism_smb.create(grid, prefix+"pism_smb",
		ghostedp, width);
	pism_smb.set_attrs("diagnostic",
		"pism_smb",
		"m-2 s-1", "pism_smb");
	// No DELTA< does not participate in epsilon computation
	add_massenth(pism_smb, 0, "pism_smb.mass", "pism_smb.enth");

	icebin_xfer.create(grid, prefix+"icebin_xfer",
		ghostedp, width);
	icebin_xfer.set_attrs("diagnostic",
		"icebin_xfer",
		"m-2 s-1", "icebin_xfer");
	add_massenth(icebin_xfer, DELTA, "icebin_xfer.mass", "icebin_xfer.enth");

	icebin_deltah.create(grid, prefix+"icebin_deltah",
		ghostedp, width);
	icebin_deltah.set_attrs("diagnostic",
		"icebin_deltah",
		"J m-2 s-1", "icebin_deltah");
	add_enth(icebin_deltah, DELTA, "");

	href_to_h.create(grid, prefix+"href_to_h",
		ghostedp, width);
	href_to_h.set_attrs("diagnostic",
		"href_to_h",
		"kg m-2 s-1", "href_to_h");
	add_mass(href_to_h, 0, "");

	nonneg_rule.create(grid, prefix+"nonneg_rule",
		ghostedp, width);
	nonneg_rule.set_attrs("diagnostic",
		"nonneg_rule",
		"kg m-2 s-1", "nonneg_rule");
	add_mass(nonneg_rule, 0, "");



	melt_grounded.create(grid, prefix+"melt_grounded",
		ghostedp, width);
	melt_grounded.set_attrs("diagnostic",
		"Basal melting of grounded ice (negative)",
		"m-2 s-1", "melt_grounded");
	add_massenth(melt_grounded, DELTA, "melt_grounded.mass", "melt_grounded.enth");

	melt_floating.create(grid, prefix+"melt_floating",
		ghostedp, width);
	melt_floating.set_attrs("diagnostic",
		"Sub-shelf melting (negative)",
		"m-2 s-1", "melt_floating");
	add_massenth(melt_floating, DELTA, "melt_floating.mass", "melt_floating.enth");

	// ----------- Advection WITHIN the ice sheet
	internal_advection.create(grid, prefix+"internal_advection",
		ghostedp, width);
	internal_advection.set_attrs("diagnostic",
		"Advection within the ice sheet",
		"m-2 s-1", "internal_advection");
	add_massenth(internal_advection, DELTA, "internal_advection.mass", "internal_advection.enth");

	// ----------- Balance the Budget
	epsilon.create(grid, prefix+"epsilon",
		ghostedp, width);
	epsilon.set_attrs("diagnostic",
		"Unaccounted-for changes",
		"m-2 s-1", "epsilon");
	add_massenth(epsilon, EPSILON, "epsilon.mass", "epsilon.enth");
}

std::ostream &MassEnergyBudget::print_formulas(std::ostream &out)
{
	// MASS
	out << "epsilon.mass = total.mass -" << std::endl;
	out << "    (";
	for (auto ii=all_vecs.begin(); ii != all_vecs.end(); ++ii) {
		if ((ii->flags & (DELTA | MASS)) != (DELTA | MASS)) continue;
		char str[20];
		sprintf(str, "%p", (void*)&ii->vec);
		out << ii->vec.get_name() << " + ";
	}
	out << ")" << std::endl;

	// Energy
	out << "epsilon.enth = total.enth -" << std::endl;
	out << "    (";
	for (auto ii=all_vecs.begin(); ii != all_vecs.end(); ++ii) {
		if ((ii->flags & (DELTA | ENTH)) != (DELTA | ENTH)) continue;
		char str[20];
		sprintf(str, "%p", (void*)&ii->vec);
		out << ii->vec.get_name() << " + ";
	}
	out << ")" << std::endl;

	return out;
}


void MassEnergyBudget::set_epsilon(pism::IceGrid::ConstPtr grid)
{
	// ==> epsilon = (sum of fluxes) - total
	printf("BEGIN MassEnergyBudget::set_epsilon()\n");

	// -------- Mass
	epsilon.mass.begin_access();
	total.mass.begin_access();
	for (int i = grid->xs(); i < grid->xs() + grid->xm(); ++i) {
	for (int j = grid->ys(); j < grid->ys() + grid->ym(); ++j) {
		epsilon.mass(i,j) = total.mass(i,j);
	}}
	total.mass.end_access();

	for (auto &ii : all_vecs) {
		if ((ii.flags & (DELTA | MASS)) != (DELTA | MASS)) continue;

		printf("epsilon.mass: %s\n", ii.vec.get_name().c_str());

		ii.vec.begin_access();
		for (int i = grid->xs(); i < grid->xs() + grid->xm(); ++i) {
		for (int j = grid->ys(); j < grid->ys() + grid->ym(); ++j) {
			epsilon.mass(i,j) -= ii.vec(i,j);
		}}
		ii.vec.end_access();
	}
	epsilon.mass.end_access();

	// -------- Energy
	epsilon.enth.begin_access();
	total.enth.begin_access();
	for (int i = grid->xs(); i < grid->xs() + grid->xm(); ++i) {
	for (int j = grid->ys(); j < grid->ys() + grid->ym(); ++j) {
		epsilon.enth(i,j) = total.enth(i,j);
	}}
	total.enth.end_access();

#if 1
	for (auto &ii : all_vecs) {
		if ((ii.flags & (DELTA | ENTH)) != (DELTA | ENTH)) continue;

		printf("epsilon.energy: %s\n", ii.vec.get_name().c_str());

		ii.vec.begin_access();
		for (int i = grid->xs(); i < grid->xs() + grid->xm(); ++i) {
		for (int j = grid->ys(); j < grid->ys() + grid->ym(); ++j) {
			epsilon.enth(i,j) -= ii.vec(i,j);
		}}
		ii.vec.end_access();
	}
#endif
	epsilon.enth.end_access();

	printf("END MassEnergyBudget::set_epsilon()\n");
}

}}
