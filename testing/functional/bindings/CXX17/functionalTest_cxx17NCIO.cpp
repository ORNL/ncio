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
    ncio::NCIO ncio;
    ncio.SetParameter("key", "value");
    SUBCASE("GetParameter") { CHECK(ncio.GetParameter("key") == "value"); }
    SUBCASE("GetNullParameter")
    {
        CHECK(ncio.GetParameter("null") == std::nullopt);
    }
    SUBCASE("GetConfigFile") { CHECK(ncio.GetConfigFile() == std::nullopt); }

    SUBCASE("OpenDataDescriptorWriteHDF5")
    {
        ncio::DataDescriptor fh = ncio.Open("empty.h5", ncio::openmode::write);

        constexpr float totalCounts = 10;
        fh.Put<ncio::schema::nexus::bank1::total_counts>(&totalCounts);
    }

    SUBCASE("OpenDataDescriptorReadHDF5")
    {
        ncio::DataDescriptor fh = ncio.Open("empty.h5", ncio::openmode::read);
    }

    ncio.SetParameter("Transport", "Null");

    SUBCASE("OpenDataDescriptorWriteNull")
    {
        ncio::DataDescriptor fh = ncio.Open("null", ncio::openmode::write);

        constexpr float dataI32 = 10;
        fh.Put<ncio::schema::nexus::bank1::total_counts>(&dataI32);
    }

    SUBCASE("OpenDataDescriptorReadNull")
    {
        ncio::DataDescriptor fh = ncio.Open("null", ncio::openmode::read);
    }
}
