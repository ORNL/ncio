/**
 * DataDescriptor.tcc: Implementation  of private core::DataDescriptor class
 * template functions.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "DataDescriptor.h"

#include "ncio/common/ncioTypes.h"
#include "ncio/schema/ncioNexus.h"

namespace ncio::core
{

#define NCIO_CORE_DATADESCRIPTOR_PUTGET_NEXUS(bank, entry, T)                  \
    template <>                                                                \
    void DataDescriptor::Put<bank, entry>(const T *data)                       \
    {                                                                          \
        m_Transport->Put(nexus::impl::ToString<bank, entry>(), data);          \
    }                                                                          \
                                                                               \
    template <>                                                                \
    void DataDescriptor::Get<bank, entry>(T * data)                            \
    {                                                                          \
        m_Transport->Get(nexus::impl::ToString<bank, entry>(), data);          \
    }

#define declare_ncio_nexus_bank_entries(T)                                     \
    NCIO_CORE_DATADESCRIPTOR_PUTGET_NEXUS(                                     \
        nexus::bank##T, nexus::bank##T::event_id, std::uint64_t)               \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_PUTGET_NEXUS(                                     \
        nexus::bank##T, nexus::bank##T::event_index, std::uint32_t)            \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_PUTGET_NEXUS(                                     \
        nexus::bank##T, nexus::bank##T::event_time_offset, float)              \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_PUTGET_NEXUS(                                     \
        nexus::bank##T, nexus::bank##T::event_time_zero, double)               \
                                                                               \
    NCIO_CORE_DATADESCRIPTOR_PUTGET_NEXUS(nexus::bank##T,                      \
                                          nexus::bank##T::total_counts, float)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_nexus_bank_entries)
#undef declare_ncio_nexus_bank_entries

} // end namespace ncio::core
