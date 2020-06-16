/**
 * Transport.h: abstract class that defines and unifies interactions to back-end
 * self-describing data libraries (e.g. HDF5) exposing functionality through a
 * common interface.
 *
 *  Created on: May 15, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <any>
#include <set>

#include "ncio/common/ncioMacros.h"
#include "ncio/common/ncioTypes.h" // openmode

namespace ncio::transport
{

class Transport
{
public:
    /**
     * Unique constructor to create a handler object from an underlying I/O
     * library
     * @param type input from derived class
     * @param descriptorName base name for file/stream
     *        - write: exact name
     *        - read: base name for searching a file/stream
     * @param openMode write or read
     * @param parameters particular set of parameters for underlying I/O library
     * from client
     */
    Transport(const std::string &type, const std::string &descriptorName,
              const openmode openMode, const Parameters &parameters);

    virtual ~Transport() = default;

    /** Retrieve current transport transport class from derived class */
    std::string GetType() const noexcept;

    /** Retrieves a Metadata Index structure as requested by clients
     * constructors */
    template <class T>
    T GetMetadata();

    /** Write a variable entry by name */
    template <class T>
    void Put(const std::string &entryName, const T *data);

    /** Read a variable entry by name */
    template <class T>
    void Get(const std::string &entryName, T *data);

    /** Close system I/O underlying resources */
    void Close();

    /**
     * Special function to retrieve the library I/O native handler
     * @return object of type any must be casted by clients using
     * `std::any_cast`
     */
    std::any GetNativeHandler() noexcept;

protected:
    /** tracks type of derived class backend used (HDF5) */
    const std::string m_Type;

    /** tracks underlying name, it's different from desciptorName */
    const std::string m_Name;

    /** open mode for tranport, write or read */
    const openmode m_OpenMode;

    /** handler to client configuration parameters */
    const Parameters &m_Parameters;

    /** flag to check if m_File is open and close it in destructor (RAII) */
    bool m_IsOpen = false;

    // here register types by overloading DoGetMetadata, not messing with move
    // semantics as it conflicts with overloading this function
    virtual void
    DoGetMetadata(std::map<std::string, std::set<std::string>> &index) = 0;

#define declare_ncio_type(T)                                                   \
    virtual void DoPut(const std::string &entryName, const T *data) = 0;       \
    virtual void DoGet(const std::string &entryName, T *data) = 0;

    NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

    virtual void DoClose() = 0;

    virtual std::any DoGetNativeHandler() noexcept = 0;
};

} // end namespace ncio::io
