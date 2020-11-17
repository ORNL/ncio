/**
 * Transport.h: class that defines and unifies interactions to back-end
 * self-describing data libraries (e.g. HDF5). Template functions
 * implementation.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "Transport.h"

namespace ncio::transport
{

template <class T>
T Transport::GetMetadata()
{
    T index;
    DoGetMetadata(index);
    return index;
}

// REGISTER TYPES for GetMetadata
template std::map<std::string, std::set<std::string>> Transport::GetMetadata();

template <class T>
void Transport::Put(const std::string &entryName, const T *data,
                    const Dimensions &dimensions, const int threadID)
{
    DoPut(entryName, data, dimensions, threadID);
}

// REGISTER TYPES for Put
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

// REGISTER TYPES for Get
#define declare_ncio_type(T)                                                   \
    template void Transport::Get<T>(const std::string &, T *, const Box &,     \
                                    const int threadID);

NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

} // end namespace ncio::io
