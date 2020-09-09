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
void DataDescriptor::Put(const T *data, const int threadID)
{
    assert(m_ImplDataDescriptor != nullptr);
    m_ImplDataDescriptor->Put<decltype(entry), entry>(data, threadID);
}

template <auto entry, class T>
void DataDescriptor::Get(T *data, const int threadID)
{
    assert(m_ImplDataDescriptor != nullptr);
    m_ImplDataDescriptor->Get<decltype(entry), entry>(data, threadID);
}

} // end namespace ncio

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "schema/nexus/cxx17DataDescriptorNexus.tcc"
#endif
