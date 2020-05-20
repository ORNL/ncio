/**
 * cxx17NCIO.h : public C++17 header to the NCIO class
 *
 *  Created on: May 8, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <memory> //std::unique_ptr
#include <string>

#include "cxx17DataDescriptor.h"
#include "ncio/common/ncioTypes.h"

namespace ncio
{
/// \cond EXCLUDE_FROM_DOXYGEN
// forward declare private implementation
namespace core
{
class NCIO;
}
/// \endcond

class NCIO
{
public:
    /**
     * NCIO constructor, it's the starting point of contact within the NCIO
     * library and an application
     * @param configFile optional input runtime configuration
     * TODO define format
     * Options:
     *  yaml : popular, allows commenting out pieces
     *  json : popular, subset of yaml that doesn't allow commenting
     */
    NCIO(const std::string &configFile = "");

    /**
     * Can't use default destructor since std::unique_ptr private implementation
     * can't have incomplete types
     */
    ~NCIO();

    /**
     * Get configuration file name passed in constructor
     * @return configuration file name
     */
    std::string GetConfigFile() const noexcept;

    /**
     * Set a specific configuration parameter, meant to be equivalent to values
     * in constructor's configFile Using small string optimization SSO (passing
     * by value) as parameters are expected to be small strings. If key exists
     * it replaces the current value.
     * @param key input parameter key
     * @param value input parameter value
     */
    void SetParameter(const std::string key, const std::string value) noexcept;

    /**
     * Returns the value of a parameter found by key.
     * @param key input parameter key to search in existing set parameters.
     * @return parameter value, if key not found returns an empty string.
     */
    std::string GetParameter(const std::string key) const noexcept;

    /**
     * Creates a DataDescriptor object
     * @param name unique DataDescriptor identifier
     * @param mode openmode::write, openmore::read
     * @return a valid object that executes the I/O data movement operations
     * @throws exception of type std::system_error or std::invalid_argument
     */
    DataDescriptor Open(const std::string &name, const openmode mode);

private:
    /** private implementation pointer owned by this class */
    std::unique_ptr<core::NCIO> m_ImplNCIO;
};

} // end namespace ncio
