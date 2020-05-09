/**
 * cxx17NCIO.h : public C++17 header to the NCIO class
 *
 *  Created on: May 8, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <memory> //std::unique_ptr
#include <string>

namespace ncio
{

namespace core
{
class NCIO; // forward declare private implementation
}

class NCIO
{
public:
    /**
     * NCIO constructor, it's the starting point of contact within the NCIO
     * library and an application
     * @param configFile optional input runtime configuration TODO format
     * (yaml?)
     */
    NCIO(const std::string &configFile = "");
    ~NCIO() = default;

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
    std::string GetParameter(const std::string key) noexcept;

private:
    /** private implementation pointer */
    std::unique_ptr<core::NCIO> m_NCIO;
};

} // end namespace ncio
