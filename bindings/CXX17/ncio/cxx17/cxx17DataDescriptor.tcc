/**
 * cxx17DataDescriptor.tcc: Implementation of DataDescriptor class template
 * functions specializations.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "cxx17DataDescriptor.h"

#include "ncio/common/ncioTypesNexus.h"
#include "ncio/core/DataDescriptor.h"

#include <cassert> //assert

namespace ncio
{

#define NCIO_DATADESCRIPTOR_GET_NEXUS(entry, T)                                \
    template <>                                                                \
    void DataDescriptor::Get<entry>(T * data)                                  \
    {                                                                          \
        assert(m_ImplDataDescriptor != nullptr);                               \
        m_ImplDataDescriptor->Get<decltype(entry), entry>(data);               \
    }

#define declare_ncio_nexus_bank_entries(T)                                     \
    NCIO_DATADESCRIPTOR_GET_NEXUS(nexus::bank##T::event_id, std::uint64_t)     \
                                                                               \
    NCIO_DATADESCRIPTOR_GET_NEXUS(nexus::bank##T::event_index, std::uint32_t)  \
                                                                               \
    NCIO_DATADESCRIPTOR_GET_NEXUS(nexus::bank##T::event_time_offset, float)    \
                                                                               \
    NCIO_DATADESCRIPTOR_GET_NEXUS(nexus::bank##T::event_time_zero, double)     \
                                                                               \
    NCIO_DATADESCRIPTOR_GET_NEXUS(nexus::bank##T::total_counts, float)

NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_nexus_bank_entries)
#undef declare_ncio_nexus_bank_entries

} // end namespace ncio
