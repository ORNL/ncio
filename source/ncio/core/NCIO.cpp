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

std::optional<std::string> NCIO::GetParameter(const std::string key) const
    noexcept
{
    auto itKey = m_Parameters.find(key);
    if (itKey == m_Parameters.end())
    {
        return std::nullopt;
    }
    return itKey->second;
}

core::DataDescriptor &NCIO::Open(const std::string &name,
                                 const ncio::openmode openMode)
{
    auto pair = m_DataDescriptors.emplace(
        name,
        std::make_unique<core::DataDescriptor>(name, openMode, m_Parameters));
    return *pair.first->second.get();
}

} // end namespace ncio::core
