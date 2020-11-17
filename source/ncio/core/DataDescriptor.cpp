/**
 * DataDescriptor.cpp : private C++17 implementation to the core::DataDescriptor
 * class
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "DataDescriptor.h"
#include "DataDescriptor.tcc"

#include <cassert> // assert

#include <ncioConfig.h> // for #define NCIO_HAVE_XXX

// Helpers
#include "ncio/helper/ncioHelperString.h" // ToLower

// Transports
#include "ncio/transport/TransportNull.h"

#ifdef NCIO_HAVE_HDF5
#include "ncio/transport/TransportHDF5.h"
#endif

namespace ncio::core
{

DataDescriptor::DataDescriptor(const std::string &descriptorName,
                               const OpenMode openMode,
                               const Parameters &parameters)
: m_DescriptorName(descriptorName), m_OpenMode(openMode)
{
    InitTransport(descriptorName, openMode, parameters);
}

void DataDescriptor::Execute(const int threadID)
{
    auto lf_ExecutePuts =
        [this](const std::map<std::string, std::vector<Entry>> &entriesMap,
               const int threadID) {
            for (const auto &entriesPair : entriesMap)
            {
                const std::string &entryName = entriesPair.first;
                const auto &entries = entriesPair.second;

                for (const Entry &entry : entries)
                {
                    switch (entry.dataType)
                    {
#define declare_ncio_types(T, L)                                               \
    case (T):                                                                  \
        PutEntry<L>(entryName, entry, threadID);                               \
        break;
                        NCIO_PRIMITIVE_DATATYPES_2ARGS(declare_ncio_types)
#undef declare_ncio_types
                    }
                }
            }
        };

    auto lf_ExecuteGets =
        [this](std::map<std::string, std::vector<Entry>> &requests,
               const int threadID) {
            for (auto &requestPair : requests)
            {
                const std::string &entryName = requestPair.first;
                auto &requests = requestPair.second;

                for (Entry &request : requests)
                {
                    const Box box = std::get<Box>(request.query);

                    switch (request.dataType)
                    {
#define declare_ncio_types(T, L)                                               \
    case (T):                                                                  \
        m_Transport->Get<L>(entryName, std::any_cast<L *>(request.data), box,  \
                            threadID);                                         \
        break;

                        NCIO_PRIMITIVE_DATATYPES_2ARGS(declare_ncio_types)
#undef declare_ncio_types
                    }
                }
            }
        };

    auto itThreadID = m_Entries.find(threadID);
    assert(itThreadID != m_Entries.end());

    switch (m_OpenMode)
    {
    case OpenMode::write:
        lf_ExecutePuts(itThreadID->second, threadID);
        break;

    case OpenMode::read:
        lf_ExecuteGets(itThreadID->second, threadID);
        break;

    case OpenMode::undefined:
        break;
    }

    // TODO: add option for locking requests if write/read patterns are
    // always the same
    std::lock_guard<std::mutex> lock(m_Mutex);
    itThreadID->second.clear();
}

std::future<void> DataDescriptor::ExecuteAsync(const std::launch launchMode,
                                               const int threadID)
{
    return std::async(launchMode, &DataDescriptor::Execute, this, threadID);
}

std::any DataDescriptor::GetNativeHandler() noexcept
{
    return m_Transport->GetNativeHandler();
}

// PRIVATE
DataDescriptor::Entry::Entry(const DataType dataType, std::any data,
                             const std::variant<Dimensions, Box> &query,
                             const ShapeType shapeType,
                             const Parameters &parameters, Info *info)
: dataType(dataType), data(data), query(query), shapeType(shapeType),
  parameters(parameters), info(info)
{
}

void DataDescriptor::InitMetadata(const Parameters &parameters) {}

void DataDescriptor::InitTransport(const std::string &descriptorName,
                                   const OpenMode openMode,
                                   const Parameters &parameters)
{
    bool foundTransport = false;
    for (const auto &parameter : parameters)
    {
        // using copies as these are supposed to be small string using SSO
        const std::string key = helper::string::ToLower(parameter.first);
        const std::string value = helper::string::ToLower(parameter.second);

        if (key == "transport")
        {
            foundTransport = true;
            if (value == "hdf5")
            {
#ifdef NCIO_HAVE_HDF5
                m_Transport = std::make_unique<transport::TransportHDF5>(
                    descriptorName, openMode, parameters);
#else
                std::invalid_argument("NCIO ERROR: this version of NCIO didn't "
                                      "compile with the HDF5 dependency, can't "
                                      "use transport (key) hdf5 (value) in "
                                      "configuration parameters\n");
#endif
            }
            else if (value == "null")
            {
                m_Transport = std::make_unique<transport::TransportNull>(
                    descriptorName, openMode, parameters);
            }
            else
            {
                // TODO : update error message as new transports are added
                throw std::invalid_argument(
                    "NCIO ERROR: for parameters key=transport value=" + value +
                    " is not valid. Only hdf5 and null is supported\n");
            }
        }
    }

    // defaults
    if (!foundTransport)
    {
#ifdef NCIO_HAVE_HDF5
        m_Transport = std::make_unique<transport::TransportHDF5>(
            descriptorName, openMode, parameters);
#else
        m_Transport = std::make_unique<transport::TransportNull>(
            descriptorName, openMode, parameters);
#endif
    }
}

} // end namespace ncio::core
