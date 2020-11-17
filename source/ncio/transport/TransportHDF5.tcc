/**
 * TransportHDF5.tcc:
 *
 *  Created on: Oct 22, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#pragma once

#include "TransportHDF5.h"

#include "ncio/helper/ncioHelperString.h"

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
    hid_t TransportHDF5::GetHDF5Datatype<T>()                                  \
    {                                                                          \
        return H5T_LE;                                                         \
    }

NCIO_HD5Types_MAP(declare_ncio_types)
#undef declare_ncio_types

    template <class T>
    std::vector<hid_t> TransportHDF5::CreateDataset(
        const std::string &entryName, hid_t fileSpace)
{
    const std::vector<std::string> list = helper::string::Split(entryName);
    std::vector<hid_t> datasetChain;

    hid_t groupID = m_TopGroupID;

    // create groups recursively
    if (list.size() > 1)
    {
        std::string currentGroup = "";
        for (std::size_t i = 1; i < list.size() - 1; ++i)
        {
            currentGroup = list[i];
            // if (H5Gget_objinfo(groupID, currentGroup.c_str(), 0, NULL) == 0)
            if (H5Lexists(groupID, currentGroup.c_str(), H5P_DEFAULT) == 0)
            {
                groupID = H5Gcreate2(groupID, currentGroup.c_str(), H5P_DEFAULT,
                                     H5P_DEFAULT, H5P_DEFAULT);
            }
            else
            {
                groupID = H5Gopen(groupID, currentGroup.c_str(), H5P_DEFAULT);
            }
            datasetChain.push_back(groupID);
        }
    }

    // create dataset inside the last group
    hid_t datasetID = -1;
    if (H5Lexists(groupID, list.back().c_str(), H5P_DEFAULT) == 0)
    {
        datasetID =
            H5Dcreate(groupID, list.back().c_str(), GetHDF5Datatype<T>(),
                      fileSpace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    }
    else
    {
        datasetID = H5Dopen(groupID, list.back().c_str(), H5P_DEFAULT);
    }

    datasetChain.push_back(datasetID);

    return datasetChain;
}

template <class T>
void TransportHDF5::DoPutCommon(const std::string &entryName, const T *data,
                                const Dimensions &dimensions,
                                const int threadID)
{
    // TODO: check valid entryName for HDF5
    // Single value
    if (dimensions == DimensionsValue)
    {
        hid_t fileSpace = H5Screate(H5S_SCALAR);
        const std::vector<hid_t> listIDs =
            CreateDataset<T>(entryName, fileSpace);

        H5Dwrite(listIDs.back(), GetHDF5Datatype<T>(), H5S_ALL, H5S_ALL,
                 H5P_DEFAULT, data);
    }
}

template <class T>
void TransportHDF5::DoGetCommon(const std::string &entryName, T *data,
                                const Box &box, const int threadID)
{
}

} // end namespace ncio::transport
