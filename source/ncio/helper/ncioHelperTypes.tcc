/**
 * ncioHelperTypes.tcc:
 *
 *  Created on: Sep 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#pragma once

#include "ncio/common/ncioTypes.h"

namespace ncio::helper::types
{

#define NCIO_TYPES_ENUM(MACRO)                                                 \
    MACRO(std::int8_t, datatype::int8)                                         \
    MACRO(std::int16_t, datatype::int16)                                       \
    MACRO(std::int32_t, datatype::int32)                                       \
    MACRO(std::int64_t, datatype::int64)                                       \
    MACRO(std::uint8_t, datatype::uint8)                                       \
    MACRO(std::uint16_t, datatype::uint16)                                     \
    MACRO(std::uint32_t, datatype::uint32)                                     \
    MACRO(std::uint64_t, datatype::uint64)                                     \
    MACRO(float, datatype::float32)                                            \
    MACRO(double, datatype::float64)

#define declare_ncio_types(T, L)                                               \
    template <>                                                                \
    datatype ToDatatypeEnum<T>()                                               \
    {                                                                          \
        return L;                                                              \
    }

NCIO_TYPES_ENUM(declare_ncio_types)
#undef declare_ncio_types

}
