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

    // minimal functionality tests

#ifdef NCIO_HAVE_HDF5
    SUBCASE("OpenDataDescriptorWriteHDF5")
    {
        ncio::DataDescriptor fw =
            ncio.Open("total_counts.h5", ncio::OpenMode::write);

        constexpr float totalCounts = 10;
        fw.Put<ncio::schema::nexus::bank1::total_counts>(totalCounts);
        fw.Execute();
        fw.Close();
    }

    SUBCASE("OpenDataDescriptorReadHDF5")
    {
        ncio::DataDescriptor fr =
            ncio.Open("total_counts.h5", ncio::OpenMode::read);

        float totalCounts = 0;
        fr.Get<ncio::schema::nexus::bank1::total_counts>(totalCounts);
        fr.Execute();
        fr.Close();

        CHECK_EQ(totalCounts, 10);
    }

    SUBCASE("OpenExceptions")
    {
        ncio.Open("total_counts.h5", ncio::OpenMode::read);
        CHECK_THROWS_WITH_AS(
            ncio.Open("total_counts.h5", ncio::OpenMode::read),
            "ncio ERROR: trying to Open DataDescriptor total_counts.h5 more "
            "than once is not allowed. Call DataDescriptor::Close() first\n",
            std::logic_error);
    }

    SUBCASE("CloseExceptions")
    {
        ncio::DataDescriptor fr =
            ncio.Open("total_counts.h5", ncio::OpenMode::read);
        fr.Close();
        CHECK_THROWS_WITH_AS(
            fr.Close(),
            "ncio ERROR: invalid DataDescriptor object in call to Close. "
            "Please modify your code and pass a valid DataDescriptor created "
            "with NCIO::Open that has not been previously closed\n",
            std::logic_error);
    }

    ncio.SetParameter("Transport", "Null");
#endif

    SUBCASE("OpenDataDescriptorWriteNull")
    {
        ncio::DataDescriptor fh = ncio.Open("null", ncio::OpenMode::write);

        constexpr float dataI32 = 10;
        fh.Put<ncio::schema::nexus::bank1::total_counts>(dataI32);
        fh.Execute();
        fh.Close();
    }

    SUBCASE("OpenDataDescriptorReadNull")
    {
        ncio::DataDescriptor fr = ncio.Open("null", ncio::OpenMode::read);
        float totalCounts = 0.;
        fr.Get<ncio::schema::nexus::bank1::total_counts>(totalCounts);
        fr.Execute();
        fr.Close();
    }

    ncio.SetParameter("Transport", "Unsupported");
    SUBCASE("UnsupportedTransport")
    {
        CHECK_THROWS_WITH_AS(
            ncio.Open("null", ncio::OpenMode::read),
            "ncio ERROR: for parameters key=transport value=Unsupported is not "
            "valid. Only hdf5 and null are supported\n",
            std::invalid_argument);
    }
}
