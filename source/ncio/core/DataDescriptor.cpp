/**
 * DataDescriptor.h : private C++17 implementation to the core::DataDescriptor
 * class
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "DataDescriptor.h"
#include "DataDescriptor.tcc"

namespace ncio::core
{

DataDescriptor::DataDescriptor(const std::string &fileName,
                               ncio::openmode openMode)
: m_FileName(fileName), m_OpenMode(openMode)
{
}

void DataDescriptor::Execute() {}

std::future<void> DataDescriptor::ExecuteAsync(std::launch launchMode)
{
    return std::future<void>();
}

} // end namespace ncio::core
