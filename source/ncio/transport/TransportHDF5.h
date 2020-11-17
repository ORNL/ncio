/**
 * TransportHDF5.h: class that defines and unifies interactions to the HDF5 file
 * I/O library.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/common/ncioMacros.h"
#include "ncio/transport/Transport.h"

namespace ncio::transport
{

class TransportHDF5 : public Transport
{
public:
    TransportHDF5(const std::string &name, const OpenMode openMode,
                  const Parameters &parameters);

    ~TransportHDF5();

private:
    /**
     * HDF5 file handler. It could be int (4 bytes) or int64_t (8 bytes)
     * Using std::any to keep HDF5 dependency as a private library to ncio
     */
    std::any m_File = -1;

    void
    DoGetMetadata(std::map<std::string, std::set<std::string>> &index) final;

#define declare_ncio_type(T)                                                   \
    void DoPut(const std::string &entryName, const T *data,                    \
               const Dimensions &dimensions, const int threadID) final;        \
                                                                               \
    void DoGet(const std::string &entryName, T *data, const Box &box,          \
               const int threadID) final;

    NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

    template <class T>
    void DoPutCommon(const std::string &entryName, const T *data,
                     const Dimensions &dimensions, const int threadID);

    template <class T>
    void DoGetCommon(const std::string &entryName, T *data, const Box &box,
                     const int threadID);

    void DoClose() final;

    std::any DoGetNativeHandler() noexcept final;

    template <class T, class H5T>
    H5T GetHDF5Datatype();
};

} // end namespace nexus::io
