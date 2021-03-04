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
#include "ncio/ncioConfig.h"       // definitions: NCIO_HAVE_SCHEMA_NEXUS

#ifdef NCIO_HAVE_SCHEMA_NEXUS
#include "ncio/schema/nexus/ncioTypesSchemaNexus.h"
#endif

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
              const OpenMode openMode, const Parameters &parameters);

    virtual ~Transport() = default;

    /** Retrieves a Metadata Index structure as requested by clients
     * constructors */
    template <class Enum, Enum indexModel, class T>
    T GetMetadata(const Parameters &parameters);

    template <class T>
    void PutAttribute(const std::string &entryName, const T *data,
                      const Dimensions &dimensions, const int threadID);

    /** Write a variable entry by name and optional dimensions */
    template <class T>
    void Put(const std::string &entryName, const T *data,
             const Dimensions &dimensions, const int threadID);

    /** Read a variable entry by name and optional dimensions*/
    template <class T>
    void Get(const std::string &entryName, T *data, const Box &box,
             const int threadID);

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
    const OpenMode m_OpenMode;

    /** handler to client configuration parameters */
    const Parameters &m_Parameters;

    /** flag to check if m_File is open and close it in destructor (RAII) */
    bool m_IsOpen = false;

#define declare_ncio_type(T)                                                   \
    virtual void DoPutAttribute(const std::string &attributeName,              \
                                const T *data, const Dimensions &dimensions,   \
                                const int threadID) = 0;

    NCIO_ATTRIBUTE_DATATYPES(declare_ncio_type)
#undef declare_ncio_type

#define declare_ncio_type(T)                                                   \
    virtual void DoPut(const std::string &entryName, const T *data,            \
                       const Dimensions &dimensions, const int threadID) = 0;  \
                                                                               \
    virtual void DoGet(const std::string &entryName, T *data, const Box &box,  \
                       const int threadID) = 0;

    NCIO_PRIMITIVE_TYPES(declare_ncio_type)
#undef declare_ncio_type

    virtual void DoClose() = 0;

    virtual std::any DoGetNativeHandler() noexcept = 0;

    /// REGISTER virtual DoGetMetadata to specialize GetMetadata for each
    /// derived Transport class and Schema///////
#ifdef NCIO_HAVE_SCHEMA_NEXUS
#define declare_ncio_type(T)                                                   \
    virtual void DoGetMetadataNexus(T &index,                                  \
                                    const schema::nexus::index model,          \
                                    const Parameters &parameters) = 0;

    NCIO_MACRO_NEXUS_INDEX_MODEL(declare_ncio_type)
#undef declare_ncio_type
#endif
};

}
