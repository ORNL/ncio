/**
 * unitTest_ncioHelperMath.cpp:
 *
 *  Created on: Mar 11, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#include "ncio-doctest.h"

#include "ncio/helper/ncioHelperMath.h"

#include <cstdint>

namespace ncio::testing::unit::helper
{

TEST_CASE("Unit test for ncio::helper::math functions")
{
    SUBCASE("Product")
    {
        const std::vector<std::size_t> input = {1, 2, 3};
        CHECK_EQ(ncio::helper::math::Product(input), 6);
    }
    SUBCASE("ZeroProduct")
    {
        const std::vector<std::size_t> input = {1, 2, 0};
        CHECK_EQ(ncio::helper::math::Product(input), 0);
    }
}

}
