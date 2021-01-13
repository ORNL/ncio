/**
 * Transport.h: class that defines and unifies interactions to back-end
 * self-describing data libraries (e.g. HDF5). Template functions
 * implementation.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "Transport.h"

#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"

namespace ncio::transport
{

template <class T>
void Transport::Put(const std::string &entryName, const T *data,
                    const Dimensions &dimensions, const int threadID)
{
    DoPut(entryName, data, dimensions, threadID);
}

// REGISTER GENERAL TYPES for Put
#define declare_ncio_type(T)                                                   \
    template void Transport::Put<T>(const std::string &, const T *,            \
                                    const Dimensions &, const int threadID);

NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

template <class T>
void Transport::Get(const std::string &entryName, T *data, const Box &box,
                    const int threadID)
{
    DoGet(entryName, data, box, threadID);
}

// REGISTER GENERAL TYPES for Get
#define declare_ncio_type(T)                                                   \
    template void Transport::Get<T>(const std::string &, T *, const Box &,     \
                                    const int threadID);

NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

}

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/schema/nexus/TransportNexus.tcc"
#endif
