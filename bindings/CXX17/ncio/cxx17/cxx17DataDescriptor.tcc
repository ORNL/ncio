/**
 * cxx17DataDescriptor.tcc: Implementation of DataDescriptor class template
 * functions specializations.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "cxx17DataDescriptor.h"

#include "ncio/core/DataDescriptor.h"
#include "ncio/ncioConfig.h" // #ifdef NCIO_HAVE_SCHEMA_XXX

#include <cassert> //assert

namespace ncio
{

template <auto entry, class T>
void DataDescriptor::Put(const T &data, const int threadID)
{
    CheckImpl("Put");
    const std::string entryName =
        m_ImplDataDescriptor->ToString<decltype(entry), entry>();
    m_ImplDataDescriptor->Put(entryName, data, threadID);
}

template <auto entry, class T>
void DataDescriptor::Put(const T *data, const Dimensions &dimensions,
                         const int threadID)
{
    CheckImpl("Put");
    const std::string entryName =
        m_ImplDataDescriptor->ToString<decltype(entry), entry>();
    m_ImplDataDescriptor->Put(entryName, data, dimensions, threadID);
}

template <auto entry, class T>
void DataDescriptor::Get(T &data, const int threadID)
{
    CheckImpl("Get");
    const std::string entryName =
        m_ImplDataDescriptor->ToString<decltype(entry), entry>();
    m_ImplDataDescriptor->Get(entryName, &data, threadID);
}

template <auto entry, class T>
void DataDescriptor::Get(T *data, const Box &box, const int threadID)
{
    CheckImpl("Get");
    const std::string entryName =
        m_ImplDataDescriptor->ToString<decltype(entry), entry>();
    m_ImplDataDescriptor->Get(entryName, data, box, threadID);
}

template <auto indexModel, class T>
T DataDescriptor::GetMetadata(const Parameters &parameters)
{
    CheckImpl("GetMetadata");
    return m_ImplDataDescriptor
        ->GetMetadata<decltype(indexModel), indexModel, T>(parameters);
}

} // end namespace ncio

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "schema/nexus/cxx17DataDescriptorNexus.tcc"
#endif
