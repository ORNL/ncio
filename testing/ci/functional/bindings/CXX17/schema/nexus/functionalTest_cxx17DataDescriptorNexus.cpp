/**
 * functionalTest_cxx17DataDescriptorNexus.cpp: tests for using the Nexus schema
 *
 *  Created on: Aug 5, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 *     License: BSD-3-Clause
 */

#include "ncio-doctest.h"

#include <type_traits> // std::is_enum

#include <ncio.h>

namespace ncio::testing::ci::functional
{

TEST_CASE("Test Nexus schema entries")
{
#ifdef NCIO_HAVE_SCHEMA_NEXUS
    SUBCASE("Check Nexus bank entries")
    {
        // this will unroll to check each enum type bank_*
#define declare_ncio_type(T)                                                   \
    CHECK(std::is_enum<ncio::schema::nexus::entry::bank##T##_events>::value);

        NCIO_MACRO_NEXUS_FOREACH_BANK_ID(declare_ncio_type)
#undef declare_ncio_type
    }
#endif
}

}
