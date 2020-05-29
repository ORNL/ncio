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

static_assert(std::is_same_v<hid_t, std::int64_t>,
              "This version of HDF5 didn't compile with hid_t = int64_t");

namespace ncio::transport
{

TransportHDF5::TransportHDF5(const std::string &name, const openmode openMode,
                             const Parameters &parameters)
: Transport("HDF5", name, openMode, parameters)
{

    //    hid_t fapl = H5Pcreate(H5P_FILE_ACCESS);
    //    H5Pset_fclose_degree(fapl, H5F_CLOSE_STRONG);
    //    m_File = H5Fopen(name.c_str(), H5F_ACC_RDONLY, fapl);
    //
    //    if (m_File < 0)
    //    {
    //        throw std::invalid_argument("NCIO ERROR: couldn't open HDF5 file "
    //        +
    //                                    m_Name + " with fapl " +
    //                                    std::to_string(fapl) + "\n");
    //    }
    //    m_IsOpen = true;
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
#define declare_ncio_nexus_bank_entries(T)                                     \
    void TransportHDF5::DoPut(const std::string &entryName, const T *data) {}  \
                                                                               \
    void TransportHDF5::DoGet(const std::string &entryName, T *data)           \
    {                                                                          \
        *data = 1;                                                             \
    }

NCIO_MACRO_NEXUS_TYPES(declare_ncio_nexus_bank_entries)
#undef declare_ncio_nexus_bank_entries

void TransportHDF5::DoClose()
{
    /**
herr_t status = H5Fclose(m_File);
if (status < 0)
{
    throw std::invalid_argument("NCIO ERROR: couldn't close HDF5 file " +
                                m_Name + "\n");
} */
    m_IsOpen = false;
}

std::any TransportHDF5::DoGetNativeHandler() noexcept
{
    return std::any(m_File);
}

} // end namespace ncio::io
