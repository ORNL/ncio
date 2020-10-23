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

namespace
{

/**
 * Creates groups
 * @param entryName
 * @param h5Type
 * @param filespaceID
 * @return
 */
/**
std::vector<hid_t> CreateDataset(const std::string &entryName, hid_t h5Type,
                                 hid_t filespaceID)
{
    std::vector<hid_t> datasetChain;

    std::vector<std::string> list;
    char delimiter = '/';
    int delimiterLength = 1;
    std::string s = std::string(entryName);
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        if (pos > 0)
        { // "///a/b/c" == "a/b/c"
            token = s.substr(0, pos);
            list.push_back(token);
        }
        s.erase(0, pos + delimiterLength);
    }
    list.push_back(s);

    hid_t topId = m_GroupId;
    if (list.size() > 1)
    {
        for (int i = 0; i < list.size() - 1; i++)
        {
            if (H5Lexists(topId, list[i].c_str(), H5P_DEFAULT) == 0)
            { // does not exist, so create
                topId = H5Gcreate2(topId, list[i].c_str(), H5P_DEFAULT,
                                   H5P_DEFAULT, H5P_DEFAULT);
            }
            else
            {
                topId = H5Gopen(topId, list[i].c_str(), H5P_DEFAULT);
            }
            datasetChain.push_back(topId);
        }
    }

    hid_t varCreateProperty = H5P_DEFAULT;

    hid_t dsetID = -1;
    if (H5Lexists(topId, list.back().c_str(), H5P_DEFAULT) == 0)
    {
        dsetID = H5Dcreate(topId, list.back().c_str(), h5Type, filespaceID,
                           H5P_DEFAULT, varCreateProperty, H5P_DEFAULT);
    }
    else
    {
        dsetID = H5Dopen(topId, list.back().c_str(), H5P_DEFAULT);
    }

    datasetChain.push_back(dsetID);

    // hid_t dspace = H5Dget_space(dsetID);
    // const int ndims = H5Sget_simple_extent_ndims(dspace);
    return datasetChain;
}
*/

} // end empty namespace

TransportHDF5::TransportHDF5(const std::string &name, const OpenMode openMode,
                             const Parameters &parameters)
: Transport("HDF5", name, openMode, parameters), m_File(hid_t(-1))
{
    switch (openMode)
    {
    case (OpenMode::read):
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
    case (OpenMode::write):
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
