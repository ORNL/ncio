/**
 * ncioHelperVector.h
 *
 *  Created on: Mar 11, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include "ncioHelperMath.h"

#include <vector>

namespace ncio::helper::math
{

template <class T>
T Product(const std::vector<T> &elements)
{
    static_assert(std::is_arithmetic_v<T>,
                  "only arithmetic values are allowed");
    T product = T(1);
    for (const T &element : elements)
    {
        product *= element;
    }
    return product;
}

template std::size_t Product(const std::vector<std::size_t> &);

} // end namespace
