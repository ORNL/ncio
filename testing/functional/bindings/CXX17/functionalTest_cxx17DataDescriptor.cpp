/**
 * functionalTest_cxx17DataDescriptor.cpp : functional tests for the
 * ncio::DataDescriptor C++17 bindings class using the doctest framework
 *
 *  Created on: Dec 7, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "ncio-doctest.h"

#include <chrono>
#include <future>
#include <thread>

#include <ncio.h>

TEST_CASE("Functional tests for ncio::NCIO C++17 bindings class")
{
    ncio::NCIO ncio;

    std::future<void> future;
    // minimal functionality tests for DataDescriptor, more in
    // functionalTest_cxx17DataDescriptor.cpp
#ifdef NCIO_HAVE_HDF5
    SUBCASE("WriteAsyncHDF5")
    {
        ncio::DataDescriptor fw =
            ncio.Open("nexus_async.nxs.h5", ncio::OpenMode::write);

        // put a single value
        constexpr float totalCounts = 10;
        fw.Put<ncio::schema::nexus::bank1::total_counts>(totalCounts);

        // put a 1D array
        constexpr std::array<std::uint64_t, 3> eventIndex = {1, 2, 3};
        constexpr std::size_t nx = eventIndex.size();
        fw.Put<ncio::schema::nexus::bank1::event_index>(eventIndex.data(),
                                                        {{nx}, {0}, {nx}});

        constexpr std::array<float, 3> eventTimeOffset = {1.f, 2.f, 3.f};
        fw.Put<ncio::schema::nexus::bank1::event_time_offset>(
            eventTimeOffset.data(), {{nx}, {0}, {nx}});
        // launch in a separate thread
        future = fw.ExecuteAsync(std::launch::async);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        // wait until done
        future.get();

        fw.Close();
    }

#endif
}
