/**
 * NCIO.cpp : private C++17 implementation to the core::NCIO class
 *
 *  Created on: May 8, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "NCIO.h"

namespace ncio::core
{

NCIO::NCIO(const std::optional<std::string> &configFile)
: m_ConfigFile(configFile)
{
}

std::optional<std::string> NCIO::GetConfigFile() const noexcept
{
    return m_ConfigFile;
}

void NCIO::SetParameter(const std::string key, const std::string value) noexcept
{
    m_Parameters[key] = value;
}

std::optional<std::string>
NCIO::GetParameter(const std::string key) const noexcept
{
    auto itKey = m_Parameters.find(key);
    if (itKey == m_Parameters.end())
    {
        return std::nullopt;
    }
    return itKey->second;
}

core::DataDescriptor &NCIO::Open(const std::string &name,
                                 const OpenMode openMode)
{
    auto itDataDescriptor = m_DataDescriptors.find(name);

    // doesn't exist
    if (itDataDescriptor == m_DataDescriptors.end())
    {
        auto pair = m_DataDescriptors.emplace(
            name, std::make_unique<core::DataDescriptor>(name, openMode,
                                                         m_Parameters));
        return *pair.first->second.get();
    }

    // exist
    if (itDataDescriptor->second->IsOpen())
    {
        throw std::logic_error("ncio ERROR: trying to Open DataDescriptor " +
                               name +
                               " more than once is not allowed. Call "
                               "DataDescriptor::Close() first\n");
    }

    // remove from map if it was properly closed
    m_DataDescriptors.erase(itDataDescriptor);
    // create again
    auto pair = m_DataDescriptors.emplace(
        name,
        std::make_unique<core::DataDescriptor>(name, openMode, m_Parameters));
    return *pair.first->second.get();
}

} // end namespace ncio::core
