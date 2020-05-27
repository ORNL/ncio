/**
 * cxx17nexus.h : public interface for functions inside the ncio::nexus
 * workspace targeting the Nexus schema
 *
 *  Created on: May 26, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <string>

namespace ncio::nexus::impl
{

template <class Enum, Enum enumValue>
std::string ToString() noexcept;
}
