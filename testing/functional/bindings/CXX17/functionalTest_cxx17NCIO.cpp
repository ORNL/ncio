/**
 * testNCIO.cpp : unit tests for the ncio::NCIO C++17 bindings class using the
 * doctest framework
 *
 *  Created on: May 18, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "ncio-doctest.h"

#include <ncio.h>

TEST_CASE("Function test for ncio::NCIO C++17 bindings class")
{
    ncio::NCIO ncio("");
    ncio.SetParameter("key", "value");
    SUBCASE("GetParameter") { CHECK(ncio.GetParameter("key") == "value"); }
    SUBCASE("GetConfigFile") { CHECK(ncio.GetConfigFile() == ""); }

    SUBCASE("DataDescriptor_Get")
    {
        ncio::DataDescriptor fh = ncio.Open("dummy", ncio::openmode::read);

        float total_counts = 0;
        fh.Get<ncio::nexus::bank1::total_counts>(&total_counts);
        fh.Execute();

        CHECK(total_counts == 0.f);
    }
}
