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
    switch (openMode)
    {
    case (OpenMode::read):
    {
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
    case (OpenMode::write):
    {
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
    case (OpenMode::undefined):
    {
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
void TransportHDF5::DoGetMetadata(
    std::map<std::string, std::set<std::string> > &index)
{
}

// will need to specialize for each HDF5 type
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
        throw std::invalid_argument("ncio ERROR: couldn't close HDF5 file " +
                                    m_Name + "\n");
    }
    m_IsOpen = false;
}

std::any TransportHDF5::DoGetNativeHandler() noexcept { return m_File; }

} // end namespace ncio::io
