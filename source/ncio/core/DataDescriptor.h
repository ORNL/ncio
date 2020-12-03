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
#include <mutex>
#include <variant>

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
    DataDescriptor(const std::string &descriptorName, const OpenMode openMode,
                   const Parameters &parameters);

    ~DataDescriptor() = default;

    template <class T>
    void Put(const std::string &entryName, const T &data, const int threadID);

    template <class T>
    void Put(const std::string &entryName, const T *data,
             const Dimensions &dimensions, const int threadID);

    template <class T>
    void Get(const std::string &entryName, T *data, const int threadID);

    template <class T>
    void Get(const std::string &entryName, T *data, const Box &box,
             const int threadID);

    /** Executes all Put or Get deferred tasks */
    void Execute(const int threadID);

    /**
     * Asynchronous execution for Execute function
     * @param launchMode
     *        - std::launch async (execute in the background now)
     *        - std::launch deferred (execute at future.get() )
     * @param threadID thread from which ExecuteAsync will be launched
     * @return future handler call .get() to guarantee Execute is done
     */
    std::future<void> ExecuteAsync(const std::launch launchMode,
                                   const int threadID);

    /** Close all operations with the current DataDescriptor */
    void Close();

    /**
     * Get underlying IO handler. This is for advanced users that wan't access
     * to the underlying technology.
     * @return placeholder object that must be casted by clients with
     * std::any_cast
     */
    std::any GetNativeHandler() noexcept;

    /**
     * Entry from enum defined in schema to string. To be called by
     * bindings. Must be overloaded by a schema.
     * @tparam Enum
     * @tparam enumValue
     * @return string registered in a schema from enum defining entries
     */
    template <class Enum, Enum enumValue>
    std::string ToString() const noexcept;

    /** true: is currently opened, false: is closed and can be re-opened */
    bool IsOpen() const noexcept;

    /** used by NCIO factory, set open status if reopened */
    void SetOpenStatus(const bool openStatus) noexcept;

private:
    /**
     * Placeholder for descriptor name, not necessarily the same as file name
     * in m_Transport
     */
    std::string m_DescriptorName;

    /**
     * Placeholder for the open mode passed at the constructor from NCIO factory
     */
    OpenMode m_OpenMode = OpenMode::undefined;

    /** Polymorphic object to interact with different I/O library backends.
     * TODO: this would be a container in the future. For now it's 1-to-1. */
    std::unique_ptr<transport::Transport> m_Transport;

    /** true: active, false: Close has been called */
    bool m_IsOpen;

    /**
     * Defines Entry requests for Put and Get.
     * NOTE: prioritizing readability rather than efficient memory alignment
     * (larger size element first)
     */
    struct Entry
    {
        const DataType dataType; ///< data type
        std::any data; ///< hold data pointer or value from application
        const std::variant<Dimensions, Box> query; ///< request query
        const ShapeType shapeType;
        const Parameters parameters; ///< optional parameters (e.g. compression)
        Info *info;                  // TODO

        Entry(const DataType dataType, std::any data,
              const std::variant<Dimensions, Box> &query,
              const ShapeType shapeType, const Parameters &parameters,
              Info *info);
    };

    /**
     * Placeholder for deferred entries for Put or Get
     * - key = threadID
     * - value = Entries map with current requests
     *   - key = entry name
     *   - value = vector of Entry struct requests
     */
    std::map<int, std::map<std::string, std::vector<Entry>>> m_Entries;

    /** private mutex for thread-safety operations */
    std::mutex m_Mutex;

    /** In memory metadata entry index structure. Suitable for Nexus data */
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
                       const OpenMode openMode, const Parameters &parameters);

    /**
     * Put entry into m_Transport->Put. Called at Execute for writing.
     * @tparam T
     * @param entryName
     * @param entry
     * @param thread
     */
    template <class T>
    void PutEntry(const std::string &entryName, const Entry &entry,
                  const int threadID);

    /**
     * Get entry into m_Transport->Put. Called at Execute for reading.
     * @tparam T
     * @param entryName
     * @param entry
     * @param thread
     */
    template <class T>
    void GetEntry(const std::string &entryName, Entry &entry,
                  const int threadID);
};

} // end namespace ncio::core
