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

namespace ncio::core
{

template <>
void DataDescriptor::Get<decltype(nexus::bank_1::total_counts),
                         nexus::bank_1::total_counts>(std::uint64_t *data)
{
    *data = 1;
}

} // end namespace ncio::core
