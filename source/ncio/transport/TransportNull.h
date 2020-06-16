/**
 * TransportNull.h: class that defines a null transport to help measure overhead
 * of real transports
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */
#pragma once

#include "ncio/transport/Transport.h"

namespace ncio::transport
{

class TransportNull : public Transport
{
public:
    TransportNull(const std::string &name, const openmode openMode,
                  const Parameters &parameters);

    ~TransportNull() = default;

private:
    void
    DoGetMetadata(std::map<std::string, std::set<std::string>> &index) final;

#define declare_ncio_type(T)                                                   \
    void DoPut(const std::string &entryName, const T *data) final;             \
    void DoGet(const std::string &entryName, T *data) final;

    NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

    void DoClose() final;

    std::any DoGetNativeHandler() noexcept final;
};

}
