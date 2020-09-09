/**
 * TransportHDF5.cpp: class that defines and unifies interactions to the HDF5
 * file I/O library.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "TransportHDF5.h"

#include <cassert>

#include <hdf5.h>

namespace ncio::transport
{

TransportHDF5::TransportHDF5(const std::string &name, const openmode openMode,
                             const Parameters &parameters)
: Transport("HDF5", name, openMode, parameters), m_File(hid_t(-1))
{
    switch (openMode)
    {
    case (openmode::read):
    {
        // allow for multiple handlers
        hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
        H5Pset_fclose_degree(fapl, H5F_CLOSE_STRONG);
        m_File = H5Fopen(name.c_str(), H5F_ACC_RDONLY, fapl);
        if (std::any_cast<hid_t>(m_File) < 0)
        {
            throw std::invalid_argument("ncio ERROR: couldn't open HDF5 file " +
                                        m_Name + " with fapl " +
                                        std::to_string(fapl) + "\n");
        }

        break;
    }
    case (openmode::write):
    {
        m_File =
            H5Fcreate(name.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        if (std::any_cast<hid_t>(m_File) < 0)
        {
            throw std::invalid_argument(
                "ncio ERROR: couldn't create HDF5 file " + m_Name +
                " for writing\n");
        }
        break;
    }
    }

    m_IsOpen = true;
}

TransportHDF5::~TransportHDF5()
{
    if (m_IsOpen)
    {
        Close();
    }
}

void TransportHDF5::DoGetMetadata(
    std::map<std::string, std::set<std::string> > &index)
{
}

// will need to specialize for each HDF5 type
#define declare_ncio_type(T)                                                   \
    void TransportHDF5::DoPut(const std::string &entryName, const T *data) {}  \
                                                                               \
    void TransportHDF5::DoGet(const std::string &entryName, T *data)           \
    {                                                                          \
        *data = 0;                                                             \
    }

NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

void TransportHDF5::DoClose()
{
    const herr_t status = H5Fclose(std::any_cast<hid_t>(m_File));
    if (status < 0)
    {
        throw std::invalid_argument("ncio ERROR: couldn't close HDF5 file " +
                                    m_Name + "\n");
    }
    m_IsOpen = false;
}

std::any TransportHDF5::DoGetNativeHandler() noexcept { return m_File; }

} // end namespace ncio::io
