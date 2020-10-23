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
        ncio::DataDescriptor fw = ncio.Open("empty.h5", ncio::OpenMode::write);

        constexpr float totalCounts = 10;
        fw.Put<ncio::schema::nexus::bank1::total_counts>(totalCounts);
        fw.Execute();
    }

    SUBCASE("OpenDataDescriptorReadHDF5")
    {
        ncio::DataDescriptor fh = ncio.Open("empty.h5", ncio::OpenMode::read);
        float totalCounts = 0;
        fh.Get<ncio::schema::nexus::bank1::total_counts>(totalCounts);
        fh.Execute();
    }

    ncio.SetParameter("Transport", "Null");

    SUBCASE("OpenDataDescriptorWriteNull")
    {
        ncio::DataDescriptor fh = ncio.Open("null", ncio::OpenMode::write);

        constexpr float dataI32 = 10;
        fh.Put<ncio::schema::nexus::bank1::total_counts>(dataI32);
        fh.Execute();
    }

    SUBCASE("OpenDataDescriptorReadNull")
    {
        ncio::DataDescriptor fr = ncio.Open("null", ncio::OpenMode::read);
        float totalCounts = 0.;
        fr.Get<ncio::schema::nexus::bank1::total_counts>(totalCounts);
        fr.Execute();
    }
}
