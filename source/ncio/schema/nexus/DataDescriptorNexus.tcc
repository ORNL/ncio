/**
 * DataDescriptorNexus.tcc: implements DataDescriptor specific
 * functionality to the Nexus schema for Put and Get and ToString
 *
 *  Created on: Jun 16, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"

namespace ncio::core
{
// IMPORTANT: the order matters. DataDescriptor::ToString must be implemented
// first. This is required by clang (it will fail), but not by gcc

// Implement DataDescriptor::ToString for Schema entries
#define NCIO_SCHEMA_NEXUS_TOSTRING(bank, entry)                                \
    template <>                                                                \
    std::string DataDescriptor::ToString<                                      \
        schema::nexus::bank, schema::nexus::bank::entry>() noexcept            \
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

}
