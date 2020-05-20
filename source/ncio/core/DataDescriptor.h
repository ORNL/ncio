/**
 * DataDescriptor.h : private C++17 header to the core::DataDescriptor class
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/common/ncioTypes.h"

#include <future> //std::async

namespace ncio::core
{

class DataDescriptor
{
public:
    const std::string m_FileName;
    const ncio::openmode m_OpenMode;

    DataDescriptor(const std::string &fileName, const ncio::openmode openMode);

    DataDescriptor() = delete;
    ~DataDescriptor() = default;

    //    template <class T, class U>
    //    void Put(const U *data);

    template <class Enum, Enum EnumValue, class T>
    void Get(T *data);

    void Execute();

    std::future<void> ExecuteAsync(std::launch launchMode);
};

} // end namespace ncio::core
