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
#include <numeric> // std::iota
#include <thread>

#include <ncio.h>

TEST_CASE("Functional tests for ncio::DataDescriptor C++17 bindings class")
{
    ncio::NCIO ncio;
    ncio.SetParameter("Transport", "HDF5");

#ifdef NCIO_HAVE_HDF5
    SUBCASE("WriteHDF5_async")
    {
        ncio::DataDescriptor fw =
            ncio.Open("data_async.h5", ncio::OpenMode::write);

        // put a single value
        constexpr float totalCounts = 10;
        fw.Put<ncio::schema::nexus::bank1::total_counts>(totalCounts);

        // put a 1D array
        const std::vector<std::uint64_t> eventIndex = {1, 2, 3};
        const std::size_t nx = eventIndex.size();
        fw.Put<ncio::schema::nexus::bank1::event_index>(eventIndex.data(),
                                                        {{nx}, {0}, {nx}});

        const std::vector<float> eventTimeOffset = {1.f, 2.f, 3.f};
        fw.Put<ncio::schema::nexus::bank1::event_time_offset>(
            eventTimeOffset.data(), {{nx}, {0}, {nx}});
        // launch in a separate thread and wait
        std::future future = fw.ExecuteAsync(std::launch::async);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        future.get();

        fw.Close();
    }

    SUBCASE("ReadHDF5_async")
    {
        float totalCounts = 0;
        std::vector<std::uint64_t> eventIndex(3);

        ncio::DataDescriptor fr =
            ncio.Open("data_async.h5", ncio::OpenMode::read);

        fr.Get<ncio::schema::nexus::bank1::total_counts>(totalCounts);
        fr.Get<ncio::schema::nexus::bank1::event_index>(eventIndex.data(),
                                                        ncio::BoxAll);

        std::future future = fr.ExecuteAsync(std::launch::async);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        future.get();

        fr.Close();

        CHECK_EQ(totalCounts, 10);
        CHECK_EQ(eventIndex, std::vector<std::uint64_t>{1, 2, 3});
    }

    SUBCASE("WriteHDF5_threads")
    {
        // function that writes a section of the array from a thread
        auto lf_WriteThread = [](const std::size_t threadID,
                                 const std::size_t nThreads,
                                 std::vector<float> &eventTimeOffset,
                                 ncio::DataDescriptor &fw) {
            // last
            const std::size_t shape = eventTimeOffset.size();
            const std::size_t start = (shape / nThreads) * threadID;
            const std::size_t count = (threadID == nThreads - 1)
                                          ? shape / nThreads + shape % nThreads
                                          : shape / nThreads;

            std::iota(eventTimeOffset.begin() + start,
                      eventTimeOffset.begin() + start + count,
                      static_cast<float>(start));

            // array sections
            fw.Put<ncio::schema::nexus::bank1::event_time_offset>(
                &eventTimeOffset[start], {{shape}, {start}, {count}}, threadID);

            // single value from only one thread
            if (threadID == 0)
            {
                constexpr float totalCounts = 10;
                fw.Put<ncio::schema::nexus::bank1::total_counts>(totalCounts,
                                                                 0);
            }

            fw.Execute(threadID);
        };

        std::vector<float> eventTimeOffset(1024);

        ncio::DataDescriptor fw =
            ncio.Open("data_threads.h5", ncio::OpenMode::write);

        // maximum number of threads
        const std::size_t nThreads =
            static_cast<std::size_t>(std::thread::hardware_concurrency());

        std::vector<std::thread> threads;
        threads.reserve(nThreads);

        for (std::size_t threadID = 0; threadID < nThreads; ++threadID)
        {
            threads.emplace_back(lf_WriteThread, threadID, nThreads,
                                 std::ref(eventTimeOffset), std::ref(fw));
        }

        for (auto &thread : threads)
        {
            thread.join();
        }

        fw.Close();
    }

    SUBCASE("ReadHDF5_threads")
    {
        // function that writes a section of the array from a thread
        auto lf_ReadThread = [](const std::size_t threadID,
                                const std::size_t nThreads,
                                std::vector<float> &eventTimeOffset,
                                float &totalCounts, ncio::DataDescriptor &fw) {
            // last
            const std::size_t shape = eventTimeOffset.size();
            const std::size_t start = (shape / nThreads) * threadID;
            const std::size_t count = (threadID == nThreads - 1)
                                          ? shape / nThreads + shape % nThreads
                                          : shape / nThreads;

            // array sections
            fw.Get<ncio::schema::nexus::bank1::event_time_offset>(
                &eventTimeOffset[start], {{start}, {count}}, threadID);

            // single value from only one thread
            if (threadID == 0)
            {
                fw.Get<ncio::schema::nexus::bank1::total_counts>(totalCounts,
                                                                 0);
            }

            fw.Execute(threadID);
        };

        std::vector<float> eventTimeOffsetExpected(1024);
        std::iota(eventTimeOffsetExpected.begin(),
                  eventTimeOffsetExpected.end(), 0.f);
        constexpr float totalCountsExpected = 10.f;

        std::vector<float> eventTimeOffset(1024);
        float totalCounts = 0.f;

        ncio::DataDescriptor fw =
            ncio.Open("data_threads.h5", ncio::OpenMode::read);

        // maximum number of threads
        const std::size_t nThreads =
            static_cast<std::size_t>(std::thread::hardware_concurrency());

        std::vector<std::thread> threads;
        threads.reserve(nThreads);

        for (std::size_t threadID = 0; threadID < nThreads; ++threadID)
        {
            threads.emplace_back(lf_ReadThread, threadID, nThreads,
                                 std::ref(eventTimeOffset),
                                 std::ref(totalCounts), std::ref(fw));
        }

        for (auto &thread : threads)
        {
            thread.join();
        }

        fw.Close();

        CHECK_EQ(eventTimeOffset, eventTimeOffsetExpected);
        CHECK_EQ(totalCounts, totalCountsExpected);
    }

#endif
}
