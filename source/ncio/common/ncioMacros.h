/**
 * ncioMacro.h : Define NCIO MACROS to generate and restrict possible template
 * types
 *
 * Created on: May 18, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <cstdint> //fixed-width types e.g. std::uint64_t

#include "ncio/common/ncioTypes.h"

#define NCIO_PRIMITIVE_TYPES(MACRO)                                            \
    MACRO(std::int8_t)                                                         \
    MACRO(std::int16_t)                                                        \
    MACRO(std::int32_t)                                                        \
    MACRO(std::int64_t)                                                        \
    MACRO(std::uint8_t)                                                        \
    MACRO(std::uint16_t)                                                       \
    MACRO(std::uint32_t)                                                       \
    MACRO(std::uint64_t)                                                       \
    MACRO(float)                                                               \
    MACRO(double)

#define NCIO_PRIMITIVE_DATATYPES_2ARGS(MACRO)                                  \
    MACRO(DataType::int8, std::int8_t)                                         \
    MACRO(DataType::int16, std::int16_t)                                       \
    MACRO(DataType::int32, std::int32_t)                                       \
    MACRO(DataType::int64, std::int64_t)                                       \
    MACRO(DataType::uint8, std::uint8_t)                                       \
    MACRO(DataType::uint16, std::uint16_t)                                     \
    MACRO(DataType::uint32, std::uint32_t)                                     \
    MACRO(DataType::uint64, std::uint64_t)                                     \
    MACRO(DataType::float32, float)                                            \
    MACRO(DataType::float64, double)

#define NCIO_ATTRIBUTE_DATATYPES(MACRO)                                        \
    MACRO(std::string)                                                         \
    NCIO_PRIMITIVE_TYPES(MACRO)

#define NCIO_ATTRIBUTE_DATATYPES_2ARGS(MACRO)                                  \
    MACRO(DataType::string, std::string)                                       \
    NCIO_PRIMITIVE_DATATYPES_2ARGS(MACRO)
