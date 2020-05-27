/**
 * DataDescriptor.h : private C++17 implementation to the core::DataDescriptor
 * class
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "DataDescriptor.h"
#include "DataDescriptor.tcc"

#include "ncio/transport/TransportHDF5.h"

namespace ncio::core
{

DataDescriptor::DataDescriptor(const std::string &descriptorName,
                               const openmode openMode,
                               const Parameters &parameters)
: m_DescriptorName(descriptorName)
{
    InitTransport(descriptorName, openMode, parameters);
}

void DataDescriptor::Execute() {}

std::future<void> DataDescriptor::ExecuteAsync(const std::launch launchMode)
{
    return std::async(launchMode, &DataDescriptor::Execute, this);
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
        const std::string key = parameter.first;
        const std::string value = parameter.second;

        if (key == "transport")
        {
            foundTransport = true;
            if (value == "hdf5" || value == "HDF5")
            {
                m_Transport = std::make_unique<transport::TransportHDF5>(
                    descriptorName, openMode, parameters);
            }
            else
            {
                // TODO : update error message
                throw std::invalid_argument(
                    "NCIO ERROR: for parameters key=transport value=" + value +
                    " is not valid. Only hdf5 is supported\n");
            }
        }
    }

    if (!foundTransport)
    {
        // default
        m_Transport = std::make_unique<transport::TransportHDF5>(
            descriptorName, openMode, parameters);
    }
}

} // end namespace ncio::core
