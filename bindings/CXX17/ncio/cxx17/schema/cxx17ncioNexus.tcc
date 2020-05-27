/**
 * cxx17nexus.tcc : template implementations functions inside the ncio::nexus
 * workspace targeting the Nexus schema
 *
 *  Created on: May 26, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/common/ncioMacros.h"
#include "ncio/common/ncioTypesNexus.h"
#include "ncio/schema/ncioNexus.h"

namespace ncio::nexus
{

#define NCIO_NEXUS_TOSTRING(bank, entry)                                       \
    template <>                                                                \
    std::string ToString<bank::entry>() noexcept                               \
    {                                                                          \
        return impl::ToString<decltype(bank::entry), bank::entry>();           \
    }

#define declare_ncio_nexus_bank_entries(T)                                     \
    NCIO_NEXUS_TOSTRING(bank##T, event_id)                                     \
    NCIO_NEXUS_TOSTRING(bank##T, event_index)                                  \
    NCIO_NEXUS_TOSTRING(bank##T, event_time_offset)                            \
    NCIO_NEXUS_TOSTRING(bank##T, event_time_zero)                              \
    NCIO_NEXUS_TOSTRING(bank##T, total_counts)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_nexus_bank_entries)
#undef declare_ncio_nexus_bank_entries
}
