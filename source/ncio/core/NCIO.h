/**
 * NCIO.h : private C++17 header to the core::NCIO class
 *
 *  Created on: May 8, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncio/common/ncioTypes.h"
#include "ncio/core/DataDescriptor.h"

#include <map>
#include <optional>
#include <string>

namespace ncio::core
{

class NCIO
{
public:
    /**
     * NCIO constructor, it's the starting point of contact within the NCIO
     * library and an application
     * @param configFile optional input runtime configuration
     */
    NCIO(const std::optional<std::string> &configFile = std::nullopt);

    /** Using RAII for all members */
    ~NCIO() = default;

    /**
     * Get configuration file name passed in constructor
     * @return configuration file name
     */
    std::optional<std::string> GetConfigFile() const noexcept;

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
     * TODO: use std::optional instead
     * Returns the value of a parameter found by key.
     * @param key input parameter key to search in existing set parameters.
     * @return parameter value, if key not found returns an empty string.
     */
    std::optional<std::string> GetParameter(const std::string key) const
        noexcept;

    /**
     * Open, factory of core::DataDescriptor
     * @param fileName
     * @param openMode
     * @return internal handler
     */
    core::DataDescriptor &Open(const std::string &name,
                               const OpenMode openMode);

private:
    /** input config file passed at constructor */
    std::optional<std::string> m_ConfigFile;

    /**
     * Parameter key/value container
     * interact through SetParameter/GetParameter
     */
    std::map<std::string, std::string> m_Parameters;

    // TODO: might need to be a multimap or key might need to be a
    // std::map<unsigned int, core::DataDescriptor> to allow multiple handlers
    // needs a unique_ptr since object doesn't have a copy constructor (owns a
    // member unique_ptr) and can't be constructed with a std::pair
    std::map<std::string, std::unique_ptr<core::DataDescriptor>>
        m_DataDescriptors;
};

} // end namespace ncio
