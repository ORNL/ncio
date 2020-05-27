/*
 * nexus.tcc
 *
 *  Created on: May 26, 2020
 *      Author: wgodoy
 */

#pragma once

#include "ncio/common/ncioMacros.h"
#include "ncio/common/ncioTypesNexus.h"
#include "ncioNexus.h"

namespace ncio::nexus::impl
{

#define NCIO_NEXUS_IMPL_TOSTRING(bank, entry)                                  \
    template <>                                                                \
    std::string ToString<bank, bank::entry>() noexcept                         \
    {                                                                          \
        return std::string("/entry/").append(#bank).append("/").append(        \
            #entry);                                                           \
    }

#define declare_ncio_nexus_bank_entries(T)                                     \
    NCIO_NEXUS_IMPL_TOSTRING(bank##T, event_id)                                \
    NCIO_NEXUS_IMPL_TOSTRING(bank##T, event_index)                             \
    NCIO_NEXUS_IMPL_TOSTRING(bank##T, event_time_offset)                       \
    NCIO_NEXUS_IMPL_TOSTRING(bank##T, event_time_zero)                         \
    NCIO_NEXUS_IMPL_TOSTRING(bank##T, total_counts)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_nexus_bank_entries)
#undef declare_ncio_nexus_bank_entries

} // end namespace ncio::nexus::impl
