/**
 * unitTest_ncioHelperTypes.cpp
 *
 *  Created on: Mar 11, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#include "ncio-doctest.h"

#include "ncio/common/ncioTypes.h"
#include "ncio/helper/ncioHelperTypes.h"

#include <iostream>

namespace ncio::testing::unit::helper
{

TEST_CASE("Unit test for ncio::helper::types functions")
{
    SUBCASE("ToDataTypeEnum")
    {
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<std::string>(),
                 ncio::DataType::string);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<std::int8_t>(),
                 ncio::DataType::int8);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<std::int16_t>(),
                 ncio::DataType::int16);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<std::int32_t>(),
                 ncio::DataType::int32);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<std::int64_t>(),
                 ncio::DataType::int64);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<std::uint8_t>(),
                 ncio::DataType::uint8);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<std::uint16_t>(),
                 ncio::DataType::uint16);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<std::uint32_t>(),
                 ncio::DataType::uint32);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<std::uint64_t>(),
                 ncio::DataType::uint64);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<float>(),
                 ncio::DataType::float32);
        CHECK_EQ(ncio::helper::types::ToDataTypeEnum<double>(),
                 ncio::DataType::float64);
    }
}

} // end namespace
