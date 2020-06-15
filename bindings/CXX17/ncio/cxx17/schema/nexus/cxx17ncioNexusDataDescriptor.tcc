/**
 * cxx17ncioNexusDataDescriptor.tcc : implements DataDescriptor specific
 * functionality to the Nexus schema for Put and Get
 *
 *  Created on: Jun 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/schema/nexus/ncioTypesNexus.h"

namespace ncio
{

#define declare_ncio_type(T)                                                   \
    NCIO_CXX17_DATADESCRIPTOR_PUT_ENTRY(schema::nexus::bank##T::event_id,      \
                                        std::uint64_t)                         \
    NCIO_CXX17_DATADESCRIPTOR_PUT_ENTRY(schema::nexus::bank##T::event_index,   \
                                        std::uint32_t)                         \
    NCIO_CXX17_DATADESCRIPTOR_PUT_ENTRY(                                       \
        schema::nexus::bank##T::event_time_offset, float)                      \
    NCIO_CXX17_DATADESCRIPTOR_PUT_ENTRY(                                       \
        schema::nexus::bank##T::event_time_zero, double)                       \
    NCIO_CXX17_DATADESCRIPTOR_PUT_ENTRY(schema::nexus::bank##T::total_counts,  \
                                        float)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_type)
#undef declare_ncio_type

#define declare_ncio_type(T)                                                   \
    NCIO_CXX17_DATADESCRIPTOR_GET_ENTRY(schema::nexus::bank##T::event_id,      \
                                        std::uint64_t)                         \
    NCIO_CXX17_DATADESCRIPTOR_GET_ENTRY(schema::nexus::bank##T::event_index,   \
                                        std::uint32_t)                         \
    NCIO_CXX17_DATADESCRIPTOR_GET_ENTRY(                                       \
        schema::nexus::bank##T::event_time_offset, float)                      \
    NCIO_CXX17_DATADESCRIPTOR_GET_ENTRY(                                       \
        schema::nexus::bank##T::event_time_zero, double)                       \
    NCIO_CXX17_DATADESCRIPTOR_GET_ENTRY(schema::nexus::bank##T::total_counts,  \
                                        float)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_type)
#undef declare_ncio_type

}
