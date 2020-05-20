/*
 * ncioTypes.h : define public types in the ncio library.
 *
 *  Created on: May 9, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <cstddef> //std::size_t
#include <cstdint> //std::uint64_t
#include <limits>  //std::numeric_limits

#include "ncioTypesNexus.h"

namespace ncio
{
/**
 * Defines possible DataDescriptor opening modes, using bitmask to allow many
 * values at once (e.g. write) if this is required in the future
 * TODO Options:
 * 	1. enum class in ncio (current)
 * 	2. enum class in DataDescriptor
 * 	3. enum in DataDescriptor (similar interactions in 1)
 */
enum class openmode : std::uint64_t
{
    write = std::uint64_t(1) << 1, // 2^1
    read = std::uint64_t(1) << 2,  // 2^2
};

} // end namespace ncio
