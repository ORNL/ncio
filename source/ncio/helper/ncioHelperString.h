/**
 * ncioHelperString.h: string related helper functions
 *
 *  Created on: Aug 5, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#pragma once

#include <string>

namespace ncio::helper::string
{

std::string ToLower(const std::string &input) noexcept;

} // end namespace ncio::helper::string
