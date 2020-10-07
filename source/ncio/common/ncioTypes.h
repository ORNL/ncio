/**
 * ncioTypes.h : define public types in the ncio library.
 *
 *  Created on: May 9, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <cstdint> //fixed-width types e.g. std::uint64_t
#include <map>
#include <string>
#include <vector>

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
    write = std::uint64_t(1) << 1,     // 2^1
    read = std::uint64_t(1) << 2,      // 2^2
    undefined = std::uint64_t(1) << 3, // 2^3
};

// alias for passing around key/value parameters
using Parameters = std::map<std::string, std::string>;

using Shape = std::vector<std::size_t>;
using Start = std::vector<std::size_t>;
using Count = std::vector<std::size_t>;
using Dimensions = std::tuple<Shape, Start, Count>;

/** enum class for data types used internally for entries */
enum class datatype
{
    int8,
    int16,
    int32,
    int64,
    uint8,
    uint16,
    uint32,
    uint64,
    float32,
    float64
};

} // end namespace ncio
