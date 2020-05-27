/*
 * ncioTypesNexus.h : public header that defines specific NeXus types
 *
 *  Created on: May 11, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncioMacros.h"

/**
 * Define inputs to NCIO API functions that are specific to the NeXus schema
 * types mapping to datasets or variables.
 * Info about the NeXus schema: https://manual.nexusformat.org/index.html
 */
namespace ncio::nexus
{

#define declare_nexus_banks_enum_entries(T)                                    \
    NCIO_MACRO_FUNCTION_NEXUS_BANK_MAKE_ENUM(T)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_nexus_banks_enum_entries)
#undef declare_nexus_banks_enum_entries

enum class log
{
    average_value,
    average_value_error,
    device_id,
    device_name,
    maximum_value,
    minimum_value,
    time,
    value
};

enum class sample
{
    can_barcode,
    can_indicator,
    can_materials,
    can_name,
    chemical_formula,
    comments,
    component,
    container_id,
    container_name,
    description,
    height_in_container,
    identifier,
    interior_depth,
    interior_diameter,
    interior_height,
    interior_width,
    lattice_a,
    lattice_alpha,
    lattice_b,
    lattice_beta,
    lattice_c,
    lattice_gamma,
    mass,
    mass_density,
    name,
    nature,
    outer_depth,
    outer_diameter,
    outer_height,
    outer_width,
    volume_cubic
};

enum class user
{
    facility_user_id,
    name
};

} // end namespace ncio::nexus
