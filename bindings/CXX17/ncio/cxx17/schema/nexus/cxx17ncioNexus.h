/**
 * cxx17ncioNexus.h : public interface for functions inside the
 * ncio::schema::nexus workspace targeting the Nexus schema
 *
 *  Created on: May 26, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <string>

namespace ncio::schema::nexus
{

/**
 * Converts a generated ncio entry enum into a string conforming to the Nexus
 * schema
 * @return Nexus schema entry name
 */
template <auto enumValue>
std::string ToString() noexcept;
}
