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

namespace ncio::testing::ci::functional
{

TEST_CASE("Functional tests for ncio::DataDescriptor C++17 bindings class")
{
    ncio::NCIO ncio;
    ncio.SetParameter("Transport", "HDF5");

#ifdef NCIO_HAVE_HDF5
    SUBCASE("WriteHDF5_async")
    {
        ncio::DataDescriptor fw =
            ncio.Open("data_async.h5", ncio::OpenMode::write);

        fw.PutAttribute<ncio::schema::nexus::entry::NX_class, std::string>();
        fw.PutAttribute<ncio::schema::nexus::entry::bank1_events::NX_class,
                        std::string>();
        fw.PutAttribute<ncio::schema::nexus::entry::bank2_events::NX_class,
                        std::string>();

        // attributes are immutable, already created
        fw.PutAttribute<ncio::schema::nexus::entry::NX_class, std::string>();

        // put a single value
        constexpr float totalCounts = 10;
        fw.Put<ncio::schema::nexus::entry::bank1_events::total_counts>(
            totalCounts);

        // put 1D arrays
        const std::size_t nx = 3;

        const std::vector<double> eventTimeZero = {0.016667, 0.033335,
                                                   0.050003};
        fw.Put<ncio::schema::nexus::entry::bank2_events::event_time_zero>(
            eventTimeZero.data(), {{nx}, {0}, {nx}});

        const std::vector<std::uint64_t> eventIndex = {1, 2, 3};
        fw.Put<ncio::schema::nexus::entry::bank1_events::event_index>(
            eventIndex.data(), {{nx}, {0}, {nx}});

        const std::vector<std::uint32_t> eventID = {194, 335, 353};
        fw.Put<ncio::schema::nexus::entry::bank1_events::event_id>(
            eventID.data(), {{nx}, {0}, {nx}});

        const std::vector<float> eventTimeOffset = {1.f, 2.f, 3.f};
        fw.Put<ncio::schema::nexus::entry::bank1_events::event_time_offset>(
            eventTimeOffset.data(), {{nx}, {0}, {nx}});

        // launch in a separate thread and wait
        std::future future = fw.ExecuteAsync(std::launch::async);

        // std::this_thread::sleep_for(std::chrono::seconds(1));

        future.get();

        fw.Close();
    }

    SUBCASE("ReadHDF5_async")
    {
        float totalCounts = 0;
        std::vector<std::uint64_t> eventIndex(3);

        ncio::DataDescriptor fr =
            ncio.Open("data_async.h5", ncio::OpenMode::read);

        fr.Get<ncio::schema::nexus::entry::bank1_events::total_counts>(
            totalCounts);
        fr.Get<ncio::schema::nexus::entry::bank1_events::event_index>(
            eventIndex.data(), ncio::BoxAll);

        ncio::Shape bank2_eventTimeZeroShape = fr.GetShape<
            ncio::schema::nexus::entry::bank2_events::event_time_zero>();

        // currently 1D, TODO generalize to any shape
        std::vector<double> eventTimeZero;
        eventTimeZero.resize(bank2_eventTimeZeroShape.front());

        fr.Get<ncio::schema::nexus::entry::bank2_events::event_time_zero>(
            eventTimeZero.data(), ncio::BoxAll);

        std::future future = fr.ExecuteAsync(std::launch::async);
        future.get();

        fr.Close();

        CHECK_EQ(totalCounts, 10);
        CHECK_EQ(eventIndex, std::vector<std::uint64_t>{1, 2, 3});
        CHECK_EQ(eventTimeZero,
                 std::vector<double>{0.016667, 0.033335, 0.050003});
    }

    SUBCASE("ReadHDF5_vector")
    {
        float totalCounts = 0;
        // ncio would reallocate
        std::vector<std::uint64_t> eventIndex;
        std::vector<double> eventTimeZero;

        ncio::DataDescriptor fr =
            ncio.Open("data_async.h5", ncio::OpenMode::read);

        fr.Get<ncio::schema::nexus::entry::bank1_events::total_counts>(
            totalCounts);
        fr.Get<ncio::schema::nexus::entry::bank1_events::event_index>(
            eventIndex, ncio::BoxAll);

        fr.Get<ncio::schema::nexus::entry::bank2_events::event_time_zero>(
            eventTimeZero, ncio::BoxAll);

        fr.Execute();
        fr.Close();

        CHECK_EQ(totalCounts, 10);
        CHECK_EQ(eventIndex, std::vector<std::uint64_t>{1, 2, 3});
        CHECK_EQ(eventTimeZero,
                 std::vector<double>{0.016667, 0.033335, 0.050003});
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
            fw.Put<ncio::schema::nexus::entry::bank1_events::event_time_offset>(
                &eventTimeOffset[start], {{shape}, {start}, {count}}, threadID);

            // single value from only one thread
            if (threadID == 0)
            {
                constexpr float totalCounts = 10;
                fw.Put<ncio::schema::nexus::entry::bank1_events::total_counts>(
                    totalCounts, 0);
            }

            fw.Execute(threadID);
        };

        std::vector<float> eventTimeOffset(1024);

        ncio::DataDescriptor fw =
            ncio.Open("data_threads.h5", ncio::OpenMode::write);

        // maximum number of threads
        const std::size_t nThreads =
#ifdef __APPLE__
            1;
#else
            static_cast<std::size_t>(std::thread::hardware_concurrency() / 2);
#endif
        std::cout << "nThreads writers = " << nThreads << "\n";

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
            fw.Get<ncio::schema::nexus::entry::bank1_events::event_time_offset>(
                &eventTimeOffset[start], {{start}, {count}}, threadID);

            // single value from only one thread
            if (threadID == 0)
            {
                fw.Get<ncio::schema::nexus::entry::bank1_events::total_counts>(
                    totalCounts, 0);
            }

            fw.Execute(threadID);
        };

        std::vector<float> eventTimeOffsetExpected(1024);
        std::iota(eventTimeOffsetExpected.begin(),
                  eventTimeOffsetExpected.end(), 0.f);
        constexpr float totalCountsExpected = 10.f;

        std::vector<float> eventTimeOffset(1024);
        float totalCounts = 0.f;

        ncio::DataDescriptor fr =
            ncio.Open("data_threads.h5", ncio::OpenMode::read);

        const std::size_t nThreads =
#ifdef __APPLE__
            1;
#else
            static_cast<std::size_t>(std::thread::hardware_concurrency() / 2);
#endif

        std::cout << "nThreads readers = " << nThreads << "\n";

        std::vector<std::thread> threads;
        threads.reserve(nThreads);

        for (std::size_t threadID = 0; threadID < nThreads; ++threadID)
        {
            // std::ref(rf) is optional as it's a lightweight object
            threads.emplace_back(lf_ReadThread, threadID, nThreads,
                                 std::ref(eventTimeOffset),
                                 std::ref(totalCounts), std::ref(fr));
        }

        for (auto &thread : threads)
        {
            thread.join();
        }

        fr.Close();

        CHECK_EQ(eventTimeOffset, eventTimeOffsetExpected);
        CHECK_EQ(totalCounts, totalCountsExpected);
    }

    SUBCASE("GetNativeHandler")
    {
        ncio::DataDescriptor fr =
            ncio.Open("data_threads.h5", ncio::OpenMode::read);
        std::any nativeHandler = fr.GetNativeHandler();

        fr.Close();
    }

    SUBCASE("ReOpen")
    {
        ncio::DataDescriptor fr =
            ncio.Open("data_threads.h5", ncio::OpenMode::read);
        fr.Close();

        fr = ncio.Open("data_threads.h5", ncio::OpenMode::read);
        fr.Close();
    }

    SUBCASE("GetMetadata")
    {
        const std::string fileName = "data_async.h5";

        ncio::DataDescriptor fr = ncio.Open(fileName, ncio::OpenMode::read);

        const auto nxClassIndex =
            fr.GetMetadata<ncio::schema::nexus::index::model1,
                           ncio::schema::nexus::model1_t>();

        const std::map<std::string, std::set<std::string>>
            expectedNxClassIndex = {
                {"NXentry", {"/entry"}},
                {"NXevent_data",
                 {"/entry/bank1_events", "/entry/bank2_events"}},
                {"SDS",
                 {"/entry/bank1_events/event_id",
                  "/entry/bank1_events/event_index",
                  "/entry/bank1_events/event_time_offset",
                  "/entry/bank1_events/total_counts",
                  "/entry/bank2_events/event_time_zero"}}};

        for (const auto &entryPair : nxClassIndex)
        {
            std::cout << "Class: " << entryPair.first << "\n";

            for (const auto &entry : entryPair.second)
            {
                std::cout << "\nEntry: " << entry << "\n";
            }
            std::cout << "\n";
        }

        CHECK_EQ(nxClassIndex, expectedNxClassIndex);

        fr.Close();
    }
#endif
}

}
