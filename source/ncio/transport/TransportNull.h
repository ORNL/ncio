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
    TransportNull(const std::string &name, const OpenMode openMode,
                  const Parameters &parameters);

    ~TransportNull() = default;

private:
#define declare_ncio_type(T)                                                   \
    void DoPut(const std::string &entryName, const T *data,                    \
               const Dimensions &dimensions, const int threadID) final;        \
                                                                               \
    void DoGet(const std::string &entryName, T *data, const Box &dimensions,   \
               const int threadID) final;

    NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

    void DoClose() final;

    std::any DoGetNativeHandler() noexcept final;

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#define declare_ncio_type(T)                                                   \
    void DoGetMetadataNexus(T &index, const schema::nexus::index model,        \
                            const Parameters &parameters) final;

    NCIO_MACRO_NEXUS_INDEX_MODEL(declare_ncio_type)
#undef declare_ncio_type
#endif
};

}
