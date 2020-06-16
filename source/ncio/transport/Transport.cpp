/**
 * Transport.cpp: class that defines and unifies interactions to back-end
 * self-describing data libraries (e.g. HDF5).
 *
 *  Created on: May 20, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */
#include "Transport.h"
#include "Transport.tcc"

#include <cassert>

namespace ncio::transport
{

Transport::Transport(const std::string &type, const std::string &name,
                     const openmode openMode, const Parameters &parameters)
: m_Type(type), m_Name(name), m_OpenMode(openMode), m_Parameters(parameters),
  m_IsOpen(true)
{
}

std::string Transport::GetType() const noexcept { return m_Type; }

void Transport::Close()
{
    assert(m_IsOpen);
    DoClose();
    m_IsOpen = false;
}

std::any Transport::GetNativeHandler() noexcept { return DoGetNativeHandler(); }

// REGISTER TYPE for GetMetadata
template std::map<std::string, std::set<std::string>> Transport::GetMetadata();

} // end namespace ncio::io
