/**
 * unitTest_helperString.cpp:
 *
 *  Created on: Oct 28, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */
#include "ncio-doctest.h"

#include "ncio/helper/ncioHelperString.h"

#include <iostream>

TEST_CASE("Unit test for ncio::helper::string functions")
{
    SUBCASE("ToLower")
    {
        CHECK_EQ(ncio::helper::string::ToLower("ALLCAPS"), "allcaps");
        CHECK_EQ(ncio::helper::string::ToLower("SOMECaps"), "somecaps");
        CHECK_EQ(ncio::helper::string::ToLower("Numbers123"), "numbers123");
        CHECK_EQ(ncio::helper::string::ToLower("123"), "123");
    }

    SUBCASE("EndsWith")
    {
        CHECK_EQ(ncio::helper::string::EndsWith("MyName", "Name"), true);
        CHECK_EQ(ncio::helper::string::EndsWith("w123", "23"), true);
        CHECK_FALSE(ncio::helper::string::EndsWith("hell", "x"));
        CHECK_FALSE(ncio::helper::string::EndsWith("hell", "hello"));
    }

    SUBCASE("Split")
    {
        CHECK_EQ(ncio::helper::string::Split("/a/b/c"),
                 std::vector<std::string>{"", "a", "b", "c"});

        CHECK_EQ(ncio::helper::string::Split("hello world/of /hierarchy"),
                 std::vector<std::string>{"hello world", "of ", "hierarchy"});
    }
}
