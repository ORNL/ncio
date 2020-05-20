/**
 * cxx17DataDescriptor.tcc: Implementation of DataDescriptor class template
 * functions.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "cxx17DataDescriptor.h"

#include "ncio/common/ncioTypesNexus.h"
#include "ncio/core/DataDescriptor.h"

namespace ncio
{

template <>
void DataDescriptor::Get<nexus::bank_1::total_counts>(std::uint64_t *data)
{
    m_ImplDataDescriptor->Get<decltype(nexus::bank_1::total_counts),
                              nexus::bank_1::total_counts>(data);
}

} // end namespace ncio
