/**
 * cxx17ncioNexusDataDescriptor.tcc : implements DataDescriptor specific
 * functionality to the Nexus schema for Put and Get
 *
 *  Created on: Jun 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <map>
#include <set>
#include <string>

#include "ncio/cxx17/cxx17DataDescriptor.h"

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"

namespace ncio
{

template void
DataDescriptor::PutAttribute<schema::nexus::entry::NX_class, std::string>(
    const int);

#define declare_ncio_types(T)                                                  \
    template void DataDescriptor::PutAttribute<                                \
        schema::nexus::entry::bank##T##_events::NX_class, std::string>(        \
        const int);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

// use <std::string> to interpret the string literal as std::string not
// char[]
#define declare_ncio_types(T)                                                  \
    template void                                                              \
    DataDescriptor::Put<schema::nexus::entry::bank##T##_events::event_id>(     \
        const std::uint64_t *, const Dimensions &, const int);                 \
                                                                               \
    template void                                                              \
    DataDescriptor::Put<schema::nexus::entry::bank##T##_events::event_index>(  \
        const std::uint64_t *, const Dimensions &, const int);                 \
                                                                               \
    template void DataDescriptor::Put<                                         \
        schema::nexus::entry::bank##T##_events::event_time_offset>(            \
        const float *, const Dimensions &, const int);                         \
                                                                               \
    template void DataDescriptor::Put<                                         \
        schema::nexus::entry::bank##T##_events::event_time_zero>(              \
        const double *, const Dimensions &, const int);                        \
                                                                               \
    template void                                                              \
    DataDescriptor::Put<schema::nexus::entry::bank##T##_events::total_counts>( \
        const float &, const int);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

#define declare_ncio_types(T)                                                  \
                                                                               \
    template void                                                              \
    DataDescriptor::Get<schema::nexus::entry::bank##T##_events::event_id>(     \
        std::uint64_t *, const Box &, const int);                              \
                                                                               \
    template void                                                              \
    DataDescriptor::Get<schema::nexus::entry::bank##T##_events::event_index>(  \
        std::uint64_t *, const Box &, const int);                              \
                                                                               \
    template void DataDescriptor::Get<                                         \
        schema::nexus::entry::bank##T##_events::event_time_offset>(            \
        float *, const Box &, const int);                                      \
                                                                               \
    template void DataDescriptor::Get<                                         \
        schema::nexus::entry::bank##T##_events::event_time_zero>(              \
        double *, const Box &, const int);                                     \
                                                                               \
    template void                                                              \
    DataDescriptor::Get<schema::nexus::entry::bank##T##_events::total_counts>( \
        float &, const int);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

#define declare_ncio_types(T)                                                  \
    template void                                                              \
    DataDescriptor::Get<schema::nexus::entry::bank##T##_events::event_id>(     \
        std::vector<std::uint64_t> &, const Box &);                            \
                                                                               \
    template void                                                              \
    DataDescriptor::Get<schema::nexus::entry::bank##T##_events::event_index>(  \
        std::vector<std::uint64_t> &, const Box &);                            \
                                                                               \
    template void DataDescriptor::Get<                                         \
        schema::nexus::entry::bank##T##_events::event_time_offset>(            \
        std::vector<float> &, const Box &);                                    \
                                                                               \
    template void DataDescriptor::Get<                                         \
        schema::nexus::entry::bank##T##_events::event_time_zero>(              \
        std::vector<double> &, const Box &);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

#define declare_ncio_types(T)                                                  \
    template Shape DataDescriptor::GetShape<                                   \
        schema::nexus::entry::bank##T##_events::event_id>() const;             \
                                                                               \
    template Shape DataDescriptor::GetShape<                                   \
        schema::nexus::entry::bank##T##_events::event_index>() const;          \
                                                                               \
    template Shape DataDescriptor::GetShape<                                   \
        schema::nexus::entry::bank##T##_events::event_time_offset>() const;    \
                                                                               \
    template Shape DataDescriptor::GetShape<                                   \
        schema::nexus::entry::bank##T##_events::event_time_zero>() const;

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

// check MACRO generation for expansion
template schema::nexus::model1_t
DataDescriptor::GetMetadata<schema::nexus::index::model1,
                            schema::nexus::model1_t>(
    const Parameters &parameters);

}
