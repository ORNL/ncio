/**
 * cxx17NCIO.cpp : public C++17 implementation of the NCIO class
 *
 *  Created on: May 19, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "cxx17NCIO.h"

#include "cxx17DataDescriptor.h"
#include "ncio/core/NCIO.h"

namespace ncio
{

NCIO::NCIO(const std::string &configFile)
: m_ImplNCIO(std::make_unique<core::NCIO>(configFile))
{
}

NCIO::~NCIO() {}

std::string NCIO::GetConfigFile() const noexcept
{
    return m_ImplNCIO->GetConfigFile();
}

void NCIO::SetParameter(const std::string key, const std::string value) noexcept
{
    m_ImplNCIO->SetParameter(key, value);
}

std::string NCIO::GetParameter(const std::string key) const noexcept
{
    return m_ImplNCIO->GetParameter(key);
}

DataDescriptor NCIO::Open(const std::string &name, const openmode mode)
{
    return DataDescriptor(m_ImplNCIO->Open(name, mode));
}

} // end namespace ncio
