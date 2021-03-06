/**
 * cxx17DataDescriptor.cpp: class that defines and unifies interactions to a
 * single handler data descriptor for all supported data formats. Implementation
 * of DataDescriptor class.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "cxx17DataDescriptor.h"
#include "cxx17DataDescriptor.tcc"

#include "ncio/core/DataDescriptor.h"

#include <stdexcept> // std::logic_error

namespace ncio
{

// PUBLIC
DataDescriptor::operator bool() const noexcept
{
    return m_ImplDataDescriptor != nullptr ? true : false;
}

void DataDescriptor::Execute(const int threadID)
{
    // Check m_ImplDataDescriptor is valid
    CheckImpl("Execute");
    m_ImplDataDescriptor->Execute(threadID);
}

std::future<void> DataDescriptor::ExecuteAsync(const std::launch mode,
                                               const int threadID)
{
    CheckImpl("ExecuteAsync");
    return m_ImplDataDescriptor->ExecuteAsync(mode, threadID);
}

std::any DataDescriptor::GetNativeHandler()
{
    CheckImpl("GetNativeHandler");
    return m_ImplDataDescriptor->GetNativeHandler();
}

void DataDescriptor::Close()
{
    CheckImpl("Close");
    m_ImplDataDescriptor->Close();
    m_ImplDataDescriptor = nullptr;
}

// PRIVATE
void DataDescriptor::CheckImpl(const std::string &functionName) const
{
    if (!*this)
    {
        throw std::logic_error(
            "ncio ERROR: invalid DataDescriptor object in call to " +
            functionName +
            ". Please modify your code and pass a valid DataDescriptor created "
            "with NCIO::Open that has not been previously closed\n");
    }
}

// PRIVATE
DataDescriptor::DataDescriptor(core::DataDescriptor &implDataDescriptor)
: m_ImplDataDescriptor(&implDataDescriptor)
{
}

} // end namespace ncio
