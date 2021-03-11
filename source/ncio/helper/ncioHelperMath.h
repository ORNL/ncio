/**
 * ncioHelperVector.h
 *
 *  Created on: Mar 11, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <type_traits>
#include <vector>

namespace ncio::helper::math
{

/**
 * Calculate the product of all elements in a std::vector. Restricted to
 * integral types.
 * @tparam T supported numerical type
 * @param elements input vector of elements {nx, ny, nz}
 * @return product nx . ny . nz
 */
template <class T>
T Product(const std::vector<T> &elements);

} // end namespace
