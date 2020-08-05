/**
 * ncioHelperString.cpp:
 *
 *  Created on: Aug 5, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#include "ncioHelperString.h"

#include <algorithm>

namespace ncio::helper::string
{

std::string ToLower(const std::string &input) noexcept
{
    std::string lowerCase = input;
    std::transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(),
                   ::tolower);
    return lowerCase;
}

} // end namespace ncio::helper::string
