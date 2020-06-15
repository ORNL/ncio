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
#define declare_ncio_type(T)                                                   \
    CHECK(std::is_enum<ncio::schema::nexus::bank##T>::value);

        NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_type)
#undef declare_ncio_type
    }

    SUBCASE("CheckNexusEnumToString")
    {
        CHECK(ncio::schema::nexus::ToString<
                  ncio::schema::nexus::bank1::event_id>() ==
              "/entry/bank1/event_id");
    }
}
