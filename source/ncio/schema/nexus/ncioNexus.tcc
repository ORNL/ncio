/**
 * ncioNexus.tcc : implementation of public interface for template functions
 * inside the ncio::nexus workspace targeting the Nexus schema
 *
 *  Created on: May 26, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncioNexus.h"

#include "ncio/common/ncioMacros.h"
#include "ncio/schema/nexus/ncioTypesNexus.h"

namespace ncio::schema::nexus
{

#define NCIO_SCHEMA_NEXUS_TOSTRING(bank, entry)                                \
    template <>                                                                \
    std::string ToString<bank, bank::entry>() noexcept                         \
    {                                                                          \
        return std::string("/entry/").append(#bank).append("/").append(        \
            #entry);                                                           \
    }

#define declare_ncio_type(T)                                                   \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T, event_id)                              \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T, event_index)                           \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T, event_time_offset)                     \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T, event_time_zero)                       \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T, total_counts)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_type)
#undef declare_ncio_type

} // end namespace ncio::schema::nexus
