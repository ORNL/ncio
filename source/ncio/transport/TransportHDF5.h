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

#include <memory>

namespace ncio::transport
{

class TransportHDF5 : public Transport
{
public:
    TransportHDF5(const std::string &name, const openmode openMode,
                  const Parameters &parameters);

    ~TransportHDF5();

private:
    /**
     * HDF5 file handler.
     * Using alias to hid_t to keep HDF5 dependency private
     */
    std::int64_t m_File = -1;

    void
    DoGetMetadata(std::map<std::string, std::set<std::string>> &index) final;

    // void DoPut(const std::string &entryName, const float *data) final;

#define declare_ncio_nexus_bank_entries(T)                                     \
    void DoGet(const std::string &entryName, T *data) final;

    NCIO_MACRO_NEXUS_TYPES(declare_ncio_nexus_bank_entries)
#undef declare_ncio_nexus_bank_entries

    void DoClose() final;

    std::any DoGetNativeHandler() noexcept final;
};

} // end namespace nexus::io
