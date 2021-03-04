/**
 * functionalTest_cxx17NCIO.cpp : functional tests for the ncio::NCIO C++17
 * bindings class using the doctest framework
 *
 *  Created on: May 18, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "ncio-doctest.h"

#include <array>
#include <future>
#include <numeric> // std::iota
#include <thread>

#include <ncio.h>

namespace ncio::testing::ci::functional
{

TEST_CASE("Functional tests for ncio::NCIO C++17 bindings class")
{
    ncio::NCIO ncio;
    ncio.SetParameter("key", "value");
    SUBCASE("GetParameter") { CHECK(ncio.GetParameter("key") == "value"); }
    SUBCASE("GetNullParameter")
    {
        CHECK(ncio.GetParameter("null") == std::nullopt);
    }
    SUBCASE("GetConfigFile") { CHECK(ncio.GetConfigFile() == std::nullopt); }

    // minimal functionality tests for DataDescriptor, more in
    // functionalTest_cxx17DataDescriptor.cpp

#ifdef NCIO_HAVE_HDF5
    SUBCASE("OpenDataDescriptorWriteHDF5")
    {
        ncio::DataDescriptor fw =
            ncio.Open("total_counts.h5", ncio::OpenMode::write);

        // put a single value
        constexpr float totalCounts = 10;
        fw.Put<ncio::schema::nexus::entry::bank1_events::total_counts>(
            totalCounts);

        // put a 1D array
        // moving from constexpr to const, not allowed by macOS clang in CI
        const std::array<std::uint64_t, 3> eventIndex = {1, 2, 3};
        const std::size_t nx = eventIndex.size();
        fw.Put<ncio::schema::nexus::entry::bank1_events::event_index>(
            eventIndex.data(), {{nx}, {0}, {nx}});
        fw.Execute();
        fw.Close();
    }

    SUBCASE("OpenDataDescriptorReadHDF5")
    {
        float totalCounts = 0;
        std::vector<std::uint64_t> eventIndex(3);

        ncio::DataDescriptor fr =
            ncio.Open("total_counts.h5", ncio::OpenMode::read);

        fr.Get<ncio::schema::nexus::entry::bank1_events::total_counts>(
            totalCounts);
        fr.Get<ncio::schema::nexus::entry::bank1_events::event_index>(
            eventIndex.data(), ncio::BoxAll);
        fr.Execute();
        fr.Close();

        CHECK_EQ(totalCounts, 10);
        CHECK_EQ(eventIndex, std::vector<std::uint64_t>{1, 2, 3});
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

        fh.PutAttribute<ncio::schema::nexus::entry::NX_class, std::string>();
        constexpr float dataI32 = 10;
        fh.Put<ncio::schema::nexus::entry::bank1_events::total_counts>(dataI32);
        fh.Execute();
        fh.Close();
    }

    SUBCASE("OpenDataDescriptorReadNull")
    {
        ncio::DataDescriptor fr = ncio.Open("null", ncio::OpenMode::read);

        const auto nxClassIndex =
            fr.GetMetadata<ncio::schema::nexus::index::model1,
                           ncio::schema::nexus::model1_t>();
        float totalCounts = 0.;
        fr.Get<ncio::schema::nexus::entry::bank1_events::total_counts>(
            totalCounts);
        fr.Execute();
        std::any handler = fr.GetNativeHandler();
        CHECK_FALSE(handler.has_value());
        fr.Close();
    }

    SUBCASE("InvalidDataDescriptor")
    {
        ncio::DataDescriptor fr;
        float totalCounts = 0.;
        CHECK_THROWS_WITH_AS(
            fr.Get<ncio::schema::nexus::entry::bank1_events::total_counts>(
                totalCounts),
            "ncio ERROR: invalid DataDescriptor object in call to Get. Please "
            "modify your code and pass a valid DataDescriptor created "
            "with NCIO::Open that has not been previously closed\n",
            std::logic_error);

        ncio::DataDescriptor fclose = ncio.Open("null", ncio::OpenMode::read);
        fclose.Close();
        CHECK_THROWS_WITH_AS(
            fclose.Close(),
            "ncio ERROR: invalid DataDescriptor object in call to Close. "
            "Please modify your code and pass a valid DataDescriptor created "
            "with NCIO::Open that has not been previously closed\n",
            std::logic_error);
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

}
