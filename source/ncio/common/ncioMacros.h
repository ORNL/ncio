/**
 * ncioMacro.h : Define NCIO MACROS to generate and restrict possible template
 * types
 *
 * Created on: May 18, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <complex>
#include <cstdint> //fixed-width types e.g. std::uint64_t

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
    MACRO(double)                                                              \
    MACRO(std::complex<float>)                                                 \
    MACRO(std::complex<double>)
