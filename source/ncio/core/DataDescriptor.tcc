/**
 * DataDescriptor.tcc: Implementation  of private core::DataDescriptor class
 * template functions.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "DataDescriptor.h"

#include "ncio/common/ncioTypes.h" // Dimensions
#include "ncio/helper/ncioHelperTypes.h"
#include "ncio/ncioConfig.h"

namespace ncio::core
{

template <class T>
void DataDescriptor::Put(const std::string &entryName, const T *data,
                         const int threadID)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Entries[threadID][entryName].emplace_back(
        helper::types::ToDatatypeEnum<T>(), data, Dimensions());
}

template <class Enum, Enum enumValue, class T>
void DataDescriptor::Put(const T *data, const int threadID)
{
    const std::string entryName = ToString<Enum, enumValue>();
    Put(entryName, data, threadID);
}

template <class T>
void DataDescriptor::Get(const std::string &entryName, T *data,
                         const int threadID)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Entries[threadID][entryName].emplace_back(
        helper::types::ToDatatypeEnum<T>(), data, Dimensions());
}

template <class Enum, Enum enumValue, class T>
void DataDescriptor::Get(T *data, const int threadID)
{
    const std::string entryName = ToString<Enum, enumValue>();
    Get(entryName, data, threadID);
}

} // end namespace ncio::core

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/schema/nexus/DataDescriptorNexus.tcc"
#endif
