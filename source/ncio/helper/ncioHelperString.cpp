/**
 * ncioHelperString.cpp:
 *
 *  Created on: Aug 5, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#include "ncioHelperString.h"

#include <algorithm>
#include <sstream>

namespace ncio::helper::string
{

std::string ToLower(const std::string &input) noexcept
{
    std::string lowerCase = input;
    std::transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(),
                   ::tolower);
    return lowerCase;
}

bool EndsWith(const std::string &input, const std::string &suffix) noexcept
{
    bool result = false;
    if (input.size() < suffix.size())
    {
        result = false;
    }
    else
    {
        if (input.substr(input.size() - suffix.size()) == suffix)
        {
            result = true;
        }
    }
    return result;
}

std::vector<std::string> Split(const std::string &input,
                               const char delimiter) noexcept
{
    std::stringstream inputSS(input);

    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(inputSS, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

} // end namespace ncio::helper::string
