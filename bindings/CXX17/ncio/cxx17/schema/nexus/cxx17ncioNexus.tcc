/**
 * cxx17ncioNexus.tcc : template implementations functions inside the
 * ncio::schema::nexus workspace targeting the Nexus schema
 *
 *  Created on: May 26, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/schema/nexus/ncioNexus.h"
#include "ncio/schema/nexus/ncioTypesNexus.h"

namespace ncio::schema::nexus
{

#define NCIO_CXX17_SCHEMA_NEXUS_TOSTRING(bank, entry)                          \
    template <>                                                                \
    std::string ToString<bank::entry>() noexcept                               \
    {                                                                          \
        return ToString<decltype(bank::entry), bank::entry>();                 \
    }

#define declare_ncio_types(T)                                                  \
    NCIO_CXX17_SCHEMA_NEXUS_TOSTRING(bank##T, event_id)                        \
    NCIO_CXX17_SCHEMA_NEXUS_TOSTRING(bank##T, event_index)                     \
    NCIO_CXX17_SCHEMA_NEXUS_TOSTRING(bank##T, event_time_offset)               \
    NCIO_CXX17_SCHEMA_NEXUS_TOSTRING(bank##T, event_time_zero)                 \
    NCIO_CXX17_SCHEMA_NEXUS_TOSTRING(bank##T, total_counts)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types
}
