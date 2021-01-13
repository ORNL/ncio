/**
 * cxx17DataDescriptor.h: class that defines and unifies interactions to a
 * single handler data descriptor for all supported data formats
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/common/ncioTypes.h"

#include <any>
#include <future>

namespace ncio
{
/// \cond EXCLUDE_FROM_DOXYGEN
/// forward declaring friend factory class to avoid cross reference
class NCIO;

/// private implementation class
namespace core
{
class DataDescriptor;
}
/// \endcond

class DataDescriptor
{
    friend class NCIO; // to allow access to private constructor

public:
    /** Allow empty/placeholder constructor so it can be put in STL containers*/
    DataDescriptor() = default;

    /** Use RAII components only*/
    ~DataDescriptor() = default;

    /**
     * Check object validity
     * true: valid DataDescriptor object, false: invalid, might be constructed
     * using the empty constructor
     */
    explicit operator bool() const noexcept;

    /**
     * Write prefetch operation.
     * Register data pointer for a particular entry.
     * Pointer is not populated until Execute
     * @param data input data pointer to be registered, must not go out of scope
     * of be modified until Execute
     * @param dimensions input dimensions for arrays, use ncio::DimsValue for
     * single value
     * @param threadID input threadID for multithreaded code
     * @exception std::exception
     * - std::system_error: if low-level error detected
     * - std::invalid_argument:
     *   - if data is nullptr
     */

    template <auto entry, class T>
    void Put(const T &data, const int threadID = 0);

    template <auto entry, class T>
    void Put(const T *data, const Dimensions &dimensions,
             const int threadID = 0);

    template <auto entry, class T>
    void Get(T &data, const int threadID = 0);

    /**
     * Read prefetch operation. Cheap lazy evaluation function.
     * Register data pointer for a particular entry.
     * Pointer is not populated until Execute
     * @tparam entry
     * @tparam T
     * @param data input data pointer to be registered, must not go out of scope
     * of be modified until Execute
     * @param box input dimensions selection box
     * @param threadID
     * @throws std::exception
     * - std::system_error: if low-level error detected
     * - std::invalid_argument:
     *   - if data is nullptr
     */
    template <auto entry, class T>
    void Get(T *data, const Box &box, const int threadID = 0);

    /**
     * Executes system I/O to transfer memory between writing Puts and reading
     * Gets. Expensive function can be wrapped around std::async for running in
     * the background.
     * @throws std::system_error: if low-level error detected
     *         std::input_error: if thread wasn't registered
     */
    void Execute(const int threadID = 0);

    /**
     * Similar to Execute, but return a future handler to enable asynchrous I/O
     * operations.
     * @param mode std::launch::async (execute now) or std::launch::deferred
     * (execute at future.get() ) from
     * https://en.cppreference.com/w/cpp/thread/launch
     * @return C++ async handler to internal Execute task
     * @throws std::system_error: if low-level error detected
     *         std::logic_error: if object is invalid
     */
    std::future<void> ExecuteAsync(const std::launch mode,
                                   const int threadID = 0);

    /**
     * Function that returns a reference to the underlying native handler
     * std::any_cast conversion requires publicly linking the underlying
     * dependency.
     * @return generic handler as std::any
     */
    std::any GetNativeHandler() noexcept;

    /**
     * Close all operations with the current DataDescriptor. After this
     * operation any call becomes invalid.
     */
    void Close();

private:
    /**
     * Constructor only allowed for factory friend class NCIO
     * @param implDataDescriptor internal create implementation object
     */
    DataDescriptor(core::DataDescriptor &implDataDescriptor);

    /**
     * Verify if m_ImplDataDescriptor handler is valid and throws exception.
     * @param functionName name of the function involking this for better error
     * handling
     * @throws std::logic_error if m_ImplDataDescriptor is invalid (e.g. empty
     * constructor, after Close)
     */
    void CheckImpl(const std::string &functionName);

    /**
     * Non-owning pimpl core object placeholder, using pointer to allow empty
     * constructor
     */
    core::DataDescriptor *m_ImplDataDescriptor = nullptr;
};

} // end namespace ncio
