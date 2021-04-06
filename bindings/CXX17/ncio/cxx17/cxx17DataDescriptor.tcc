/**
 * cxx17DataDescriptor.tcc: Implementation of DataDescriptor class template
 * functions specializations.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "cxx17DataDescriptor.h"

#include "ncio/common/ncioMacros.h"
#include "ncio/core/DataDescriptor.h"
#include "ncio/ncioConfig.h" // #ifdef NCIO_HAVE_SCHEMA_XXX

#include <cassert> //assert

namespace ncio
{

template <auto attribute, class T>
void DataDescriptor::PutAttribute(const int threadID)
{
    CheckImpl("PutAttribute");
    const std::string attributeName =
        m_ImplDataDescriptor->ToString<decltype(attribute), attribute>();
    const T data = m_ImplDataDescriptor
                       ->AttributeData<decltype(attribute), attribute, T>();
    m_ImplDataDescriptor->PutAttribute(attributeName, data, threadID);
}

template <auto attribute, class T>
void DataDescriptor::PutAttribute(const T &data, const int threadID)
{
    //    CheckImpl("PutAttribute");
    //    const std::string attributeName =
    //        m_ImplDataDescriptor->ToString<decltype(attribute), attribute>();
    //    m_ImplDataDescriptor->PutAttribute(attributeName, data, threadID);
}

template <auto entry, class T>
inline void DataDescriptor::Put(const T &data, const int threadID)
{
    CheckImpl("Put");
    const std::string entryName =
        m_ImplDataDescriptor->ToString<decltype(entry), entry>();
    m_ImplDataDescriptor->Put(entryName, data, threadID);
}

template <auto entry, class T>
inline void DataDescriptor::Put(const T *data, const Dimensions &dimensions,
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

template <auto entry, class T>
void DataDescriptor::Get(std::vector<T> &data, const Box &box)
{
    CheckImpl("Get");
    const std::string entryName =
        m_ImplDataDescriptor->ToString<decltype(entry), entry>();
    m_ImplDataDescriptor->Get(entryName, data, box, 0);
}

template <class T>
void DataDescriptor::Get(const std::string &entryName, std::vector<T> &data,
                         const Box &box)
{
    CheckImpl("Get");
    m_ImplDataDescriptor->Get(entryName, data, box, 0);
}

#define declare_ncio_type(T)                                                   \
    template void DataDescriptor::Get(const std::string &, std::vector<T> &,   \
                                      const Box &);

NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

template <auto entry>
Shape DataDescriptor::GetShape() const
{
    CheckImpl("GetShape");
    const std::string entryName =
        m_ImplDataDescriptor->ToString<decltype(entry), entry>();
    return m_ImplDataDescriptor->GetShape(entryName);
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
