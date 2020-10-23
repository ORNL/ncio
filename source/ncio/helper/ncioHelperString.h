/**
 * ncioHelperString.h: string related helper functions
 *
 *  Created on: Aug 5, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#pragma once

#include <string>
#include <vector>

namespace ncio::helper::string
{

/**
 * Transforms input string to lower case
 * @param input
 * @return lower case string
 */
std::string ToLower(const std::string &input) noexcept;

/**
 * Check if string ends with a suffix
 * @param input
 * @param suffix
 * @return true if input ends with suffix, false otherwise
 */
bool EndsWith(const std::string &input, const std::string &suffix) noexcept;

/**
 * Split string by delimiter string /x/y/z -> {x,y,z}
 * @param input
 * @param delimiter
 * @return vector with
 */
std::vector<std::string> Split(const std::string &input,
                               const char delimiter = '/') noexcept;

} // end namespace ncio::helper::string
