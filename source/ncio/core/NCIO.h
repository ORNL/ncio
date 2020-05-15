/**
 * NCIO.h : private C++17 header to the core::NCIO class
 *
 *  Created on: May 8, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <map>
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
     * TODO config file format (yaml?)
     */
    NCIO(const std::string &configFile);

    /** Using RAII for all members */
    ~NCIO() = default;

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

private:
    /** input config file passed at constructor */
    const std::string m_ConfigFile;

    /**
     * Parameter key/value container
     * interact through SetParameter/GetParameter
     */
    std::map<std::string, std::string> m_Parameters;
};

} // end namespace ncio
