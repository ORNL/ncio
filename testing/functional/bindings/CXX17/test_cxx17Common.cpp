/**
 * testNCIO.cpp : unit tests for the ncio::NCIO C++17 bindings class using the
 * doctest framework
 *
 *  Created on: May 18, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "ncio-doctest.h"

#include <type_traits> // std::is_enum

#include <ncio.h>

TEST_CASE("Function test for ncio:: common functionality")
{
    SUBCASE("CheckEnumBanks")
    {
        // this will unroll to check each enum type bank_*
#define declare_nexus_banks_enum_entries(T)                                    \
    CHECK(std::is_enum<ncio::nexus::T>::value);

        NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_nexus_banks_enum_entries)
#undef declare_nexus_banks_enum_entries
    }
}
