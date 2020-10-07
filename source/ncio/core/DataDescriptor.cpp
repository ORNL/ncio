/**
 * DataDescriptor.cpp : private C++17 implementation to the core::DataDescriptor
 * class
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "DataDescriptor.h"
#include "DataDescriptor.tcc"

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
                               const openmode openMode,
                               const Parameters &parameters)
: m_DescriptorName(descriptorName), m_OpenMode(openMode)
{
    InitTransport(descriptorName, openMode, parameters);
}

void DataDescriptor::Execute(const int threadID)
{
    auto lf_ExecutePuts = [this](const EntryMap &entriesMap) {
        for (const auto &entryPair : entriesMap)
        {
            const std::string &entryName = entryPair.first;
            const auto &requests = entryPair.second;

            for (const auto &request : requests)
            {
                const datatype type = std::get<0>(request);
                const std::any &data = std::get<1>(request);
                // const Dimensions &dimensions = std::get<2>(request);

                switch (type)
                {
#define declare_ncio_types(T, L)                                               \
    case (T):                                                                  \
        m_Transport->Put<L>(entryName, std::any_cast<const L *>(data));        \
        break;

                    NCIO_PRIMITIVE_DATATYPES_2ARGS(declare_ncio_types)
#undef declare_ncio_types
                }
            }
        }
    };

    auto lf_ExecuteGets = [this](EntryMap &entriesMap) {
        for (auto &entryPair : entriesMap)
        {
            const std::string &entryName = entryPair.first;
            auto &requests = entryPair.second;

            for (auto &request : requests)
            {
                const datatype type = std::get<0>(request);
                std::any &data = std::get<1>(request);
                // const Dimensions &dimensions = std::get<2>(request);

                switch (type)
                {
#define declare_ncio_types(T, L)                                               \
    case (T):                                                                  \
        m_Transport->Get<L>(entryName, std::any_cast<L *>(data));              \
        break;

                    NCIO_PRIMITIVE_DATATYPES_2ARGS(declare_ncio_types)
#undef declare_ncio_types
                }
            }
        }
    };

    auto itThreadID = m_Entries.find(threadID);
    if (itThreadID == m_Entries.end())
    {
        throw std::invalid_argument(
            "ncio ERROR: invalid threadID in call to Execute, no Put or Get "
            "calls made from threadID " +
            std::to_string(threadID) + "\n");
    }

    if (m_OpenMode == openmode::write)
    {
        lf_ExecutePuts(itThreadID->second);
    }
    else if (m_OpenMode == openmode::read)
    {
        lf_ExecuteGets(itThreadID->second);
    }

    // Clear all the requests for this thread
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

void DataDescriptor::InitMetadata(const Parameters &parameters) {}

void DataDescriptor::InitTransport(const std::string &descriptorName,
                                   const openmode openMode,
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
