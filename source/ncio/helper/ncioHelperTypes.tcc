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
    MACRO(std::string, DataType::string)                                       \
    MACRO(std::int8_t, DataType::int8)                                         \
    MACRO(std::int16_t, DataType::int16)                                       \
    MACRO(std::int32_t, DataType::int32)                                       \
    MACRO(std::int64_t, DataType::int64)                                       \
    MACRO(std::uint8_t, DataType::uint8)                                       \
    MACRO(std::uint16_t, DataType::uint16)                                     \
    MACRO(std::uint32_t, DataType::uint32)                                     \
    MACRO(std::uint64_t, DataType::uint64)                                     \
    MACRO(float, DataType::float32)                                            \
    MACRO(double, DataType::float64)

#define declare_ncio_types(T, L)                                               \
    template <>                                                                \
    DataType ToDataTypeEnum<T>() noexcept                                      \
    {                                                                          \
        return L;                                                              \
    }

NCIO_TYPES_ENUM(declare_ncio_types)
#undef declare_ncio_types

}
