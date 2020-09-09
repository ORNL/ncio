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

#define declare_ncio_types(T)                                                  \
    template void DataDescriptor::Put<schema::nexus::bank##T,                  \
                                      schema::nexus::bank##T::event_id>(       \
        const std::uint64_t *, const int);                                     \
                                                                               \
    template void DataDescriptor::Put<schema::nexus::bank##T,                  \
                                      schema::nexus::bank##T::event_index>(    \
        const std::uint32_t *, const int);                                     \
                                                                               \
    template void DataDescriptor::Put<                                         \
        schema::nexus::bank##T, schema::nexus::bank##T::event_time_offset>(    \
        const float *, const int);                                             \
                                                                               \
    template void DataDescriptor::Put<                                         \
        schema::nexus::bank##T, schema::nexus::bank##T::event_time_zero>(      \
        const double *, const int);                                            \
                                                                               \
    template void DataDescriptor::Put<schema::nexus::bank##T,                  \
                                      schema::nexus::bank##T::total_counts>(   \
        const float *, const int);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

#define declare_ncio_types(T)                                                  \
    template void DataDescriptor::Get<schema::nexus::bank##T,                  \
                                      schema::nexus::bank##T::event_id>(       \
        std::uint64_t *, const int);                                           \
                                                                               \
    template void DataDescriptor::Get<schema::nexus::bank##T,                  \
                                      schema::nexus::bank##T::event_index>(    \
        std::uint32_t *, const int);                                           \
                                                                               \
    template void DataDescriptor::Get<                                         \
        schema::nexus::bank##T, schema::nexus::bank##T::event_time_offset>(    \
        float *, const int);                                                   \
                                                                               \
    template void DataDescriptor::Get<                                         \
        schema::nexus::bank##T, schema::nexus::bank##T::event_time_zero>(      \
        double *, const int);                                                  \
                                                                               \
    template void DataDescriptor::Get<schema::nexus::bank##T,                  \
                                      schema::nexus::bank##T::total_counts>(   \
        float *, const int);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

}
