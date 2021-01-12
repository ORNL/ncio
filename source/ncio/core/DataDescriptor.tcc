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

#include "ncio/transport/Transport.h"

namespace ncio::core
{

template <class T>
void DataDescriptor::Put(const std::string &entryName, const T &data,
                         const int threadID)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Entries[threadID][entryName].emplace_back(
        helper::types::ToDataTypeEnum<T>(), data, DimensionsValue,
        ShapeType::value, Parameters(), nullptr);
}

template <class T>
void DataDescriptor::Put(const std::string &entryName, const T *data,
                         const Dimensions &dimensions, const int threadID)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Entries[threadID][entryName].emplace_back(
        helper::types::ToDataTypeEnum<T>(), data, dimensions, ShapeType::array,
        Parameters(), nullptr);
}

template <class T>
void DataDescriptor::Get(const std::string &entryName, T *data,
                         const int threadID)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Entries[threadID][entryName].emplace_back(
        helper::types::ToDataTypeEnum<T>(), data, BoxValue, ShapeType::value,
        Parameters(), nullptr);
}

template <class T>
void DataDescriptor::Get(const std::string &entryName, T *data, const Box &box,
                         const int threadID)
{
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Entries[threadID][entryName].emplace_back(
        helper::types::ToDataTypeEnum<T>(), data, box, ShapeType::array,
        Parameters(), nullptr);
}

#define declare_ncio_type(T)                                                   \
    template void DataDescriptor::Put(const std::string &, const T &,          \
                                      const int);                              \
    template void DataDescriptor::Put(const std::string &, const T *,          \
                                      const Dimensions &, const int);          \
                                                                               \
    template void DataDescriptor::Get(const std::string &, T *, const int);    \
    template void DataDescriptor::Get(const std::string &, T *, const Box &,   \
                                      const int);

NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

// PRIVATE
template <class T>
void DataDescriptor::PutEntry(const std::string &entryName, const Entry &entry,
                              const int threadID)
{
    switch (entry.shapeType)
    {
    case (ShapeType::value): {
        const T *data = std::any_cast<const T>(&entry.data);
        std::lock_guard<std::mutex> lock(m_Mutex);
        {
            m_Transport->Put(entryName, data, DimensionsValue, threadID);
        }
        break;
    }
    case (ShapeType::array): {
        // TODO some checks on Dimensions
        const T *data = std::any_cast<const T *>(entry.data);
        std::lock_guard<std::mutex> lock(m_Mutex);
        {
            m_Transport->Put(entryName, data, std::get<Dimensions>(entry.query),
                             threadID);
        }
        break;
    }
    }
}

template <class T>
void DataDescriptor::GetEntry(const std::string &entryName, Entry &entry,
                              const int threadID)
{
    switch (entry.shapeType)
    {
    case (ShapeType::value): {
        T *data = std::any_cast<T>(&entry.data);
        std::lock_guard<std::mutex> lock(m_Mutex);
        {
            m_Transport->Get(entryName, data, DimensionsValue, threadID);
        }
        break;
    }
    case (ShapeType::array): {
        // TODO some checks on Dimensions
        T *data = std::any_cast<T *>(entry.data);
        std::lock_guard<std::mutex> lock(m_Mutex);
        {
            m_Transport->Get(entryName, data, std::get<Box>(entry.query),
                             threadID);
        }
        break;
    }
    }
}

} // end namespace ncio::core

// Schema implements ncio::core::DataDescriptor::ToString
#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/schema/nexus/DataDescriptorNexus.tcc"
#endif
