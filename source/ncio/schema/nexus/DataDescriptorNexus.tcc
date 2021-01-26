/**
 * DataDescriptorNexus.tcc: implements DataDescriptor specific
 * functionality to the Nexus schema for Put and Get and ToString
 *
 *  Created on: Jun 16, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */
#pragma once

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"

namespace ncio::core
{
// IMPORTANT: the order matters. DataDescriptor::ToString must be implemented
// first. This is required by clang (it will fail), but not by gcc

// Implement DataDescriptor::ToString for Schema entries
#define NCIO_SCHEMA_NEXUS_TOSTRING(bankID_events, entryName)                   \
    template <>                                                                \
    std::string                                                                \
    DataDescriptor::ToString<schema::nexus::entry::bankID_events,              \
                             schema::nexus::entry::bankID_events::entryName>() \
        const noexcept                                                         \
    {                                                                          \
        return std::string("/entry/")                                          \
            .append(#bankID_events)                                            \
            .append("/")                                                       \
            .append(#entryName);                                               \
    }

#define declare_ncio_type(T)                                                   \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T##_events, event_id)                     \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T##_events, event_index)                  \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T##_events, event_time_offset)            \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T##_events, event_time_zero)              \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T##_events, total_counts)                 \
    NCIO_SCHEMA_NEXUS_TOSTRING(bank##T##_events, NX_class)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_type)
#undef declare_ncio_type

#define NCIO_SCHEMA_NEXUS_BANKID_NX_Class(bankID_events)                       \
    template <>                                                                \
    std::string DataDescriptor::AttributeData<                                 \
        decltype(schema::nexus::entry::bankID_events::NX_class),               \
        schema::nexus::entry::bankID_events::NX_class, std::string>()          \
        const noexcept                                                         \
    {                                                                          \
        return "NXevent_data";                                                 \
    }

#define declare_ncio_type(T) NCIO_SCHEMA_NEXUS_BANKID_NX_Class(bank##T##_events)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_type)
#undef declare_ncio_type

template <>
std::string
DataDescriptor::ToString<int, schema::nexus::entry::NX_class>() const noexcept
{
    return "/entry/NX_class";
}

template <>
std::string DataDescriptor::AttributeData<int, schema::nexus::entry::NX_class,
                                          std::string>() const noexcept
{
    return "NXentry";
}

// In-memory INDEX
template schema::nexus::model1_t
DataDescriptor::GetMetadata<schema::nexus::index, schema::nexus::index::model1,
                            schema::nexus::model1_t>(
    const Parameters &parameters);
}
