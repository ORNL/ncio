/**
 * DataDescriptor.tcc: Implementation  of private core::DataDescriptor class
 * template functions.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "DataDescriptor.h"

#include "ncio/ncioConfig.h"

namespace ncio::core
{

template <class T>
void DataDescriptor::Put(const std::string &entryName, const T *data)
{
    m_Transport->Put(entryName, data);
}

template <class Enum, Enum enumValue, class T>
void DataDescriptor::Put(const T *data)
{
    const std::string entryName = ToString<Enum, enumValue>();
    Put(entryName, data);
}

template <class T>
void DataDescriptor::Get(const std::string &entryName, T *data)
{
    m_Transport->Get(entryName, data);
}

template <class Enum, Enum enumValue, class T>
void DataDescriptor::Get(T *data)
{
    const std::string entryName = ToString<Enum, enumValue>();
    Get(entryName, data);
}

} // end namespace ncio::core

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/schema/nexus/DataDescriptorNexus.tcc"
#endif
