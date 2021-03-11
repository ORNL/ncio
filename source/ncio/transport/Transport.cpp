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
                     const OpenMode openMode, const Parameters &parameters)
: m_Type(type), m_Name(name), m_OpenMode(openMode), m_Parameters(parameters),
  m_IsOpen(true)
{
}

void Transport::Close()
{
    DoClose();
    m_IsOpen = false;
}

Shape Transport::GetShape(const std::string &entryName) const
{
    return DoGetShape(entryName);
}

std::any Transport::GetNativeHandler() noexcept { return DoGetNativeHandler(); }

}
