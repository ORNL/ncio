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
#define NCIO_CXX17_DATADESCRIPTOR_PUT_ENTRY(entry, T)                          \
    template <>                                                                \
    void DataDescriptor::Put<entry>(const T *data)                             \
    {                                                                          \
        assert(m_ImplDataDescriptor != nullptr);                               \
        m_ImplDataDescriptor->Put<decltype(entry), entry>(data);               \
    }

#define NCIO_CXX17_DATADESCRIPTOR_GET_ENTRY(entry, T)                          \
    template <>                                                                \
    void DataDescriptor::Get<entry>(T * data)                                  \
    {                                                                          \
        assert(m_ImplDataDescriptor != nullptr);                               \
        m_ImplDataDescriptor->Get<decltype(entry), entry>(data);               \
    }
} // end namespace ncio

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "schema/nexus/cxx17ncioNexusDataDescriptor.tcc"
#endif
