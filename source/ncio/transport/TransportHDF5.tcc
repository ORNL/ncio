/**
 * TransportHDF5.tcc:
 *
 *  Created on: Oct 22, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#pragma once

#include "TransportHDF5.h"

#include <hdf5.h>

namespace ncio::transport
{

#define NCIO_HD5Types_MAP(MACRO)                                               \
    MACRO(std::int8_t, H5T_STD_I8LE)                                           \
    MACRO(std::int16_t, H5T_STD_I16LE)                                         \
    MACRO(std::int32_t, H5T_STD_I32LE)                                         \
    MACRO(std::int64_t, H5T_STD_I64LE)                                         \
    MACRO(std::uint8_t, H5T_STD_U8LE)                                          \
    MACRO(std::uint16_t, H5T_STD_U16LE)                                        \
    MACRO(std::uint32_t, H5T_STD_U32LE)                                        \
    MACRO(std::uint64_t, H5T_STD_U64LE)                                        \
    MACRO(float, H5T_IEEE_F32LE)                                               \
    MACRO(double, H5T_IEEE_F64LE)

#define declare_ncio_types(T, H5T_LE)                                          \
    template <>                                                                \
    hid_t TransportHDF5::GetHDF5Datatype<T, hid_t>()                           \
    {                                                                          \
        return H5T_LE;                                                         \
    }

NCIO_HD5Types_MAP(declare_ncio_types)
#undef declare_ncio_types

    template <class T>
    void TransportHDF5::DoPutCommon(const std::string &entryName, const T *data,
                                    const Dimensions &dimensions,
                                    const int threadID)
{
    // hid_t datasetID;
    // hid_t type = GetHDF5Datatype<T, hid_t>();

    // Single value
    if (dimensions == DimensionsValue)
    {
    }

    // space = H5Screate_simple(2, , NULL);

    // int status = H5Dwrite(datasetID, , )
}

template <class T>
void TransportHDF5::DoGetCommon(const std::string &entryName, T *data,
                                const Box &box, const int threadID)
{
}

} // end namespace ncio::transport
