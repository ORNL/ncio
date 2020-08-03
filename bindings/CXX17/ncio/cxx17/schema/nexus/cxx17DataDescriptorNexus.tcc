/**
 * cxx17ncioNexusDataDescriptor.tcc : implements DataDescriptor specific
 * functionality to the Nexus schema for Put and Get
 *
 *  Created on: Jun 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"

namespace ncio
{

#define declare_ncio_types(T)                                                  \
    template void DataDescriptor::Put<schema::nexus::bank##T::event_id>(       \
        const std::uint64_t *);                                                \
    template void DataDescriptor::Put<schema::nexus::bank##T::event_index>(    \
        const std::uint32_t *);                                                \
    template void                                                              \
    DataDescriptor::Put<schema::nexus::bank##T::event_time_offset>(            \
        const float *);                                                        \
    template void                                                              \
    DataDescriptor::Put<schema::nexus::bank##T::event_time_zero>(              \
        const double *);                                                       \
    template void DataDescriptor::Put<schema::nexus::bank##T::total_counts>(   \
        const float *);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

#define declare_ncio_types(T)                                                  \
    template void DataDescriptor::Get<schema::nexus::bank##T::event_id>(       \
        std::uint64_t *);                                                      \
    template void DataDescriptor::Get<schema::nexus::bank##T::event_index>(    \
        std::uint32_t *);                                                      \
    template void                                                              \
    DataDescriptor::Get<schema::nexus::bank##T::event_time_offset>(float *);   \
    template void                                                              \
    DataDescriptor::Get<schema::nexus::bank##T::event_time_zero>(double *);    \
    template void DataDescriptor::Get<schema::nexus::bank##T::total_counts>(   \
        float *);

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_types)
#undef declare_ncio_types

}
