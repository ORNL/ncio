/**
 * DataDescriptor.h : private C++17 header to the core::DataDescriptor class
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/common/ncioTypes.h"
#include "ncio/transport/Transport.h"

#include <any>
#include <future>
#include <memory> //std::unique_ptr

namespace ncio::core
{

class DataDescriptor
{
public:
    /**
     * Implementation of DataDescriptor pointing a file/stream
     * @param descriptorName file name
     * @param openMode write or read
     * @param parameters particular configuration parameters for constructing a
     * data descriptor
     */
    DataDescriptor(const std::string &descriptorName,
                   const ncio::openmode openMode, const Parameters &parameters);

    ~DataDescriptor() = default;

    template <class T>
    void Put(const std::string &entryName, const T *data);

    template <class Enum, Enum enumValue, class T>
    void Put(const T *data);

    template <class T>
    void Get(const std::string &entryName, T *data);

    template <class Enum, Enum enumValue, class T>
    void Get(T *data);

    /** Executes all Put or Get deferred tasks */
    void Execute();

    /**
     * Asynchronous execution for Execute function
     * @param launchMode
     *        - std::launch async (execute in the background now)
     *        - std::launch deferred (execute at future.get() )
     * @return future handler call .get() to guarantee Execute is done
     */
    std::future<void> ExecuteAsync(const std::launch launchMode);

    /**
     * Get underlying IO handler. This is for advanced users that wan't access
     * to the underlying technology.
     * @return placeholder object that must be casted by clients with
     * std::any_cast
     */
    std::any GetNativeHandler() noexcept;

private:
    /**
     * Placeholder for descriptor name, not necessarily the same as file name
     * in m_Transport
     */
    std::string m_DescriptorName;

    /** Polymorphic object to interact with different I/O library backends */
    std::unique_ptr<transport::Transport> m_Transport;

    /** In memory metadata index structure. Suitable for Nexus data */
    std::map<std::string, std::set<std::string>> m_MetadataIndex1;

    /** Init relevant metadata structures */
    void InitMetadata(const Parameters &parameters);

    /**
     * Init transport backend resources (e.g. open a file)
     * @param descriptorName input descriptor name (e.g. file name)
     * @param openMode write or read
     * @param parameters key/value parameters passed to backends
     */
    void InitTransport(const std::string &descriptorName,
                       const openmode openMode, const Parameters &parameters);

    /**
     * Must be overloaded by a plugin
     * @tparam Enum
     * @tparam enumValue
     * @return
     */
    template <class Enum, Enum enumValue>
    std::string ToString() noexcept;
};

} // end namespace ncio::core

#include "DataDescriptor.inl"
