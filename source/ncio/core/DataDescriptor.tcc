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
#include "ncio/transport/Transport.h"

#include "ncio/ncioConfig.h"

namespace ncio::core
{

template <class T>
void DataDescriptor::PutAttribute(const std::string &entryName, const T &data,
                                  const int threadID)
{
    auto itFind = m_Attributes.find(entryName);
    if (itFind != m_Attributes.end())
    {
        return; // already created
    }
    std::lock_guard<std::mutex> lock(m_Mutex);
    m_Attributes.emplace(entryName,
                         Entry(helper::types::ToDataTypeEnum<T>(), data,
                               DimensionsValue, ShapeType::value, Parameters(),
                               nullptr));
}

template <class T>
void DataDescriptor::PutAttribute(const std::string &attributeName,
                                  const T *data, const Dimensions &dimensions,
                                  const int threadID)
{
    // TODO: array attributes
}

#define declare_ncio_type(T)                                                   \
    template void DataDescriptor::PutAttribute(const std::string &, const T &, \
                                               const int);                     \
                                                                               \
    template void DataDescriptor::PutAttribute(const std::string &, const T *, \
                                               const Dimensions &, const int);

NCIO_ATTRIBUTE_DATATYPES(declare_ncio_type)
#undef declare_ncio_type

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

template <class Enum, Enum indexModel, class T>
T DataDescriptor::GetMetadata(const Parameters &parameters)
{
    // for now it assumes metadata is 1-to-1 from a single transport
    return m_Transport->GetMetadata<Enum, indexModel, T>(parameters);
}

// PRIVATE
template <class T>
void DataDescriptor::PutAttributeEntry(const std::string &attributeName,
                                       const Entry &entry, const int threadID)
{
    switch (entry.shapeType)
    {
    case (ShapeType::value): {
        const T *data = std::any_cast<const T>(&entry.data);
        std::lock_guard<std::mutex> lock(m_Mutex);
        {
            m_Transport->PutAttribute(attributeName, data, DimensionsValue,
                                      threadID);
        }
        break;
    }
    case (ShapeType::array): {
        break;
    }
    }
}

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
        // TODO: rethink when backends allow truly threaded code
        std::lock_guard<std::mutex> lock(m_Mutex);
        {
            m_Transport->Get(entryName, data, DimensionsValue, threadID);
        }
        break;
    }
    case (ShapeType::array): {
        // TODO some checks on Dimensions
        T *data = std::any_cast<T *>(entry.data);
        // TODO: rethink when backends allow truly threaded code
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

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/schema/nexus/DataDescriptorNexus.tcc"
#endif
