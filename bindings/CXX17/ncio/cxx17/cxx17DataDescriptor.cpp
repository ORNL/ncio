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

#include <cassert> //assert

namespace ncio
{

// PUBLIC TODO add checks for nullptr
void DataDescriptor::Execute()
{
    assert(!m_ImplDataDescriptor);
    m_ImplDataDescriptor->Execute();
}

std::future<void> DataDescriptor::ExecuteAsync(std::launch mode)
{
    assert(!m_ImplDataDescriptor);
    return m_ImplDataDescriptor->ExecuteAsync(mode);
}

// PRIVATE
DataDescriptor::DataDescriptor(core::DataDescriptor &implDataDescriptor)
: m_ImplDataDescriptor(&implDataDescriptor)
{
}

} // end namespace ncio
