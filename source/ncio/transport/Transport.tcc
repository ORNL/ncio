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

template <class T>
void Transport::Put(const std::string &entryName, const T *data)
{
    DoPut(entryName, data);
}

template <class T>
void Transport::Get(const std::string &entryName, T *data)
{
    DoGet(entryName, data);
}

#define declare_ncio_nexus_bank_entries(T)                                     \
    template void Transport::Put(const std::string &entryName, const T *data); \
    template void Transport::Get(const std::string &entryName, T *data);

NCIO_MACRO_NEXUS_TYPES(declare_ncio_nexus_bank_entries)
#undef declare_ncio_nexus_bank_entries

} // end namespace ncio::io
