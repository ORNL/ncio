/**
 * TransportHDF5.cpp: class that defines and unifies interactions to the HDF5
 * file I/O library.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "TransportHDF5.h"
#include "TransportHDF5.tcc"

#include <cassert>

#include <hdf5.h>

namespace ncio::transport
{

TransportHDF5::TransportHDF5(const std::string &name, const OpenMode openMode,
                             const Parameters &parameters)
: Transport("HDF5", name, openMode, parameters)
{
    // Prevent seg faults at exit due to unnecessary cleanup
    // https://support.hdfgroup.org/HDF5/doc/RM/RM_H5.html#Library-DontAtExit
    H5dont_atexit();

    switch (openMode)
    {
    case (OpenMode::read): {
        hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
        // multiple handlers is not recommended by HDF5
        // H5Pset_fclose_degree(fapl, H5F_CLOSE_STRONG);
        // https://support.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Open
        m_File = H5Fopen(name.c_str(), H5F_ACC_RDONLY, fapl);
        if (m_File < 0)
        {
            throw std::invalid_argument("ncio ERROR: couldn't open HDF5 file " +
                                        m_Name + " with fapl " +
                                        std::to_string(fapl) + "\n");
        }

        break;
    }
    case (OpenMode::write): {
        m_File =
            H5Fcreate(name.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

        if (m_File < 0)
        {
            throw std::invalid_argument(
                "ncio ERROR: couldn't create HDF5 file " + m_Name +
                " for writing\n");
        }

        m_TopGroupID = H5Gopen2(m_File, "/", H5P_DEFAULT);

        break;
    }
    case (OpenMode::undefined): {
    }
    } // end switch

    m_IsOpen = true;
}

TransportHDF5::~TransportHDF5()
{
    if (m_IsOpen)
    {
        Close();
    }
}

// PRIVATE
Shape TransportHDF5::DoGetShape(const std::string &entryName) const
{
    hid_t dataSetID = H5Dopen(m_File, entryName.c_str(), H5P_DEFAULT);
    hid_t dataspaceID = H5Dget_space(dataSetID);
    const std::size_t nDimensions =
        static_cast<std::size_t>(H5Sget_simple_extent_ndims(dataspaceID));

    std::vector<unsigned long long int> shapeInt(nDimensions);
    H5Sget_simple_extent_dims(dataspaceID, shapeInt.data(), NULL);

    Shape shape;
    shape.reserve(nDimensions);

    for (const auto dimension : shapeInt)
    {
        shape.push_back(dimension);
    }

    H5Sclose(dataspaceID);
    H5Dclose(dataSetID);

    return shape;
}

#define declare_ncio_type(T)                                                   \
    void TransportHDF5::DoPutAttribute(                                        \
        const std::string &entryName, const T *data,                           \
        const Dimensions &dimensions, const int threadID)                      \
    {                                                                          \
        DoPutAttributeCommon(entryName, data, dimensions, threadID);           \
    }

NCIO_ATTRIBUTE_DATATYPES(declare_ncio_type)
#undef declare_ncio_type

#define declare_ncio_type(T)                                                   \
    void TransportHDF5::DoPut(const std::string &entryName, const T *data,     \
                              const Dimensions &dimensions,                    \
                              const int threadID)                              \
    {                                                                          \
        DoPutCommon(entryName, data, dimensions, threadID);                    \
    }                                                                          \
                                                                               \
    void TransportHDF5::DoGet(const std::string &entryName, T *data,           \
                              const Box &box, const int threadID)              \
    {                                                                          \
        DoGetCommon(entryName, data, box, threadID);                           \
    }

NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

void TransportHDF5::DoClose()
{
    const herr_t status = H5Fclose(m_File);
    if (status < 0)
    {
        throw std::runtime_error("ncio ERROR: couldn't close HDF5 file " +
                                 m_Name + "\n");
    }
    m_IsOpen = false;
}

std::any TransportHDF5::DoGetNativeHandler() noexcept { return m_File; }

void TransportHDF5::CloseDataset(std::vector<hid_t> &handlers)
{
    for (std::size_t i = 0; i < handlers.size(); ++i)
    {
        if (i == handlers.size() - 1)
        {
            H5Dclose(handlers[i]);
        }
        else
        {
            H5Gclose(handlers[i]);
        }
    }
}

} // end namespace ncio::io
