/**
 * ncioNexusDataDescriptor.tcc: implements DataDescriptor specific
 * functionality to the Nexus schema for Put and Get
 *
 *  Created on: Jun 16, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "ncio/schema/nexus/ncioNexus.h" // ToString
#include "ncio/schema/nexus/ncioTypesNexus.h"

// namespace of core::DataDescriptor
namespace ncio::core
{

#define NCIO_CORE_DATADESCRIPTOR_PUT_NEXUS_ENTRY(bank, entry, T)               \
    template <>                                                                \
    void DataDescriptor::Put<bank, entry>(const T *data)                       \
    {                                                                          \
        m_Transport->Put(schema::nexus::ToString<bank, entry>(), data);        \
    }

#define NCIO_CORE_DATADESCRIPTOR_GET_NEXUS_ENTRY(bank, entry, T)               \
    template <>                                                                \
    void DataDescriptor::Get<bank, entry>(T * data)                            \
    {                                                                          \
        m_Transport->Get(schema::nexus::ToString<bank, entry>(), data);        \
    }

#define declare_ncio_type(T)                                                   \
    NCIO_CORE_DATADESCRIPTOR_PUT_NEXUS_ENTRY(schema::nexus::bank##T,           \
                                             schema::nexus::bank##T::event_id, \
                                             std::uint64_t)                    \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_PUT_NEXUS_ENTRY(                                  \
        schema::nexus::bank##T, schema::nexus::bank##T::event_index,           \
        std::uint32_t)                                                         \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_PUT_NEXUS_ENTRY(                                  \
        schema::nexus::bank##T, schema::nexus::bank##T::event_time_offset,     \
        float)                                                                 \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_PUT_NEXUS_ENTRY(                                  \
        schema::nexus::bank##T, schema::nexus::bank##T::event_time_zero,       \
        double)                                                                \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_PUT_NEXUS_ENTRY(                                  \
        schema::nexus::bank##T, schema::nexus::bank##T::total_counts, float)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_type)
#undef declare_ncio_type

#define declare_ncio_types(T)                                                  \
    NCIO_CORE_DATADESCRIPTOR_GET_NEXUS_ENTRY(schema::nexus::bank##T,           \
                                             schema::nexus::bank##T::event_id, \
                                             std::uint64_t)                    \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_GET_NEXUS_ENTRY(                                  \
        schema::nexus::bank##T, schema::nexus::bank##T::event_index,           \
        std::uint32_t)                                                         \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_GET_NEXUS_ENTRY(                                  \
        schema::nexus::bank##T, schema::nexus::bank##T::event_time_offset,     \
        float)                                                                 \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_GET_NEXUS_ENTRY(                                  \
        schema::nexus::bank##T, schema::nexus::bank##T::event_time_zero,       \
        double)                                                                \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_GET_NEXUS_ENTRY(                                  \
        schema::nexus::bank##T, schema::nexus::bank##T::total_counts, float)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types
}
