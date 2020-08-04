/**
 * DataDescriptor.inl: template inline functions implementation in
 * DataDescriptor class. Prefer DataDesciptor.tcc for specific type
 * specialization. This is only used for default behaviors of specialized
 * functions.
 *
 *  Created on: Aug 4, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#pragma once

namespace ncio::core
{

template <class Enum, Enum enumValue>
inline std::string DataDescriptor::ToString() noexcept
{
    return "";
}

} // end namespace ncio::core
