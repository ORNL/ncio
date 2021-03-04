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
    MACRO(std::string, H5T_STRING)                                             \
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
    std::vector<hid_t> TransportHDF5::CreateIDs(const std::string &entryName,
                                                hid_t fileSpace,
                                                const bool isDataSet)
{
    const std::vector<std::string> list = helper::string::Split(entryName);
    if (list.size() <= 1)
    {
        throw std::invalid_argument(
            "ncio ERROR: couldn't create hid_t for entry " + entryName +
            " in file " + m_Name + "\n");
    }

    std::vector<hid_t> datasetChain;

    hid_t groupID = m_TopGroupID;

    // create groups recursively

    std::string currentGroup = "";
    for (std::size_t i = 1; i < list.size() - 1; ++i)
    {
        currentGroup = list[i];

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

    if (!isDataSet)
    {
        return datasetChain;
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

// specialize for std::string
template <>
void TransportHDF5::DoPutAttributeCommon<std::string>(
    const std::string &attributeName, const std::string *data,
    const Dimensions &dimensions, const int threadID)
{
    // support attribute string writing with HDF5
    if (dimensions == DimensionsValue)
    {
        // check if attribute exist, if it does don't overwrite. First come,
        // first served.
        hid_t attributeID = H5Aexists(m_File, attributeName.c_str());
        if (attributeID != 0)
        {
            return;
        }

        hid_t attributeSpace = H5Screate(H5S_SCALAR);
        hid_t attributeType = H5Tcopy(H5T_C_S1);
        H5Tset_size(attributeType, data->size());
        H5Tset_strpad(attributeType, H5T_STR_NULLTERM);

        const std::vector<hid_t> ids =
            CreateIDs<int>(attributeName, attributeSpace, false);

        const std::vector<std::string> list =
            helper::string::Split(attributeName);

        attributeID = H5Acreate2(ids.back(), list.back().c_str(), attributeType,
                                 attributeSpace, H5P_DEFAULT, H5P_DEFAULT);

        H5Awrite(attributeID, attributeType, data->c_str());
        H5Sclose(attributeSpace);
        H5Tclose(attributeType);
        H5Aclose(attributeID);
    }
}

template <class T>
inline void TransportHDF5::DoPutAttributeCommon(const std::string &entryName,
                                                const T *data,
                                                const Dimensions &dimensions,
                                                const int threadID)
{
}

template <class T>
void TransportHDF5::DoPutCommon(const std::string &entryName, const T *data,
                                const Dimensions &dimensions,
                                const int threadID)
{
    auto lf_H5SCreateSimple =
        [](const std::vector<std::size_t> &input) -> hid_t {
        return H5Screate_simple(static_cast<int>(input.size()),
                                reinterpret_cast<hsize_t *>(
                                    const_cast<std::size_t *>(input.data())),
                                NULL);
    };

    // TODO: check valid entryName for HDF5
    // single value (aka scalar)
    if (dimensions == DimensionsValue)
    {
        hid_t fileSpace = H5Screate(H5S_SCALAR);
        std::vector<hid_t> listIDs = CreateIDs<T>(entryName, fileSpace);
        hid_t datasetID = listIDs.back();
        hid_t status = H5Dwrite(datasetID, GetHDF5Datatype<T>(), H5S_ALL,
                                H5S_ALL, H5P_DEFAULT, data);
        // TODO capture status
        if (status < 0)
        {
            throw std::runtime_error("ncio ERROR: couldn't write entry " +
                                     entryName + " to HDF5 file " + m_Name +
                                     "\n");
        }
        CloseDataset(listIDs);
    }
    // array
    else
    {
        const auto [shape, start, count] = dimensions;

        // create file space and dataset
        hid_t fileSpace = lf_H5SCreateSimple(shape);
        std::vector<hid_t> listIDs = CreateIDs<T>(entryName, fileSpace);

        // retrieve fileSpace from dataset and set hyperslab box selection
        hid_t datasetID = listIDs.back();
        fileSpace = H5Dget_space(datasetID);

        // FIXME address empty count
        H5Sselect_hyperslab(fileSpace, H5S_SELECT_SET,
                            reinterpret_cast<hsize_t *>(
                                const_cast<std::size_t *>(start.data())),
                            NULL,
                            reinterpret_cast<hsize_t *>(
                                const_cast<std::size_t *>(count.data())),
                            NULL);

        // actual memory space
        hid_t memorySpace = count.empty() ? lf_H5SCreateSimple(shape)
                                          : lf_H5SCreateSimple(count);
        const hid_t status =
            H5Dwrite(datasetID, GetHDF5Datatype<T>(), memorySpace, fileSpace,
                     H5P_DEFAULT, data);

        if (status < 0)
        {
            throw std::runtime_error("ncio ERROR: couldn't write entry " +
                                     entryName + " to HDF5 file " + m_Name +
                                     "\n");
        }
        CloseDataset(listIDs);
    }
}

template <class T>
void TransportHDF5::DoGetCommon(const std::string &entryName, T *data,
                                const Box &box, const int threadID)
{

    hid_t dataSetID = H5Dopen(m_File, entryName.c_str(), H5P_DEFAULT);
    // TODO check dataSetID for errors

    if (box == BoxValue)
    {
        hid_t status = H5Dread(dataSetID, GetHDF5Datatype<T>(), H5S_ALL,
                               H5S_ALL, H5P_DEFAULT, data);
        if (status < 0)
        {
            throw std::runtime_error("ncio ERROR: couldn't read entry " +
                                     entryName + " from HDF5 file " + m_Name +
                                     "\n");
        }
        H5Dclose(dataSetID);
    }
    // array with Box selection
    else
    {
        const auto [start, count] = box;
        hid_t fileSpace = H5Dget_space(dataSetID); /* dataspace handle */

        H5Sselect_hyperslab(fileSpace, H5S_SELECT_SET,
                            reinterpret_cast<hsize_t *>(
                                const_cast<std::size_t *>(start.data())),
                            NULL,
                            reinterpret_cast<hsize_t *>(
                                const_cast<std::size_t *>(count.data())),
                            NULL);

        // actual memory space
        hid_t memorySpace =
            H5Screate_simple(static_cast<int>(count.size()),
                             reinterpret_cast<hsize_t *>(
                                 const_cast<std::size_t *>(count.data())),
                             NULL);
        hid_t status = H5Dread(dataSetID, GetHDF5Datatype<T>(), memorySpace,
                               fileSpace, H5P_DEFAULT, data);
        if (status < 0)
        {
            throw std::runtime_error("ncio ERROR: couldn't read array entry " +
                                     entryName + " from HDF5 file " + m_Name +
                                     "\n");
        }
    }
}

}

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/schema/nexus/TransportHDF5Nexus.tcc"
#endif
