
#include "cxx17NCIO.h"

#include "ncio/core/NCIO.h"

namespace ncio
{

NCIO::NCIO(const std::string &configFile)
: m_NCIO(std::make_unique<core::NCIO>(configFile))
{
}

void NCIO::SetParameter(const std::string key, const std::string value) noexcept
{
    m_NCIO->SetParameter(key, value);
}

std::string NCIO::GetParameter(const std::string key) noexcept
{
    return m_NCIO->GetParameter(key);
}

} // end namespace ncio
