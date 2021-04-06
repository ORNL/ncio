

#include "nightlyTest_NexusData.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>

#include <ncio.h>

#include <nlohmann/json.hpp>

namespace ncio::testing::regression
{

#ifdef NCIO_HAVE_HDF5
TEST_CASE_FIXTURE(NexusData, "Regression nightly tests for nexus HDF5 data")
{
    ncio::NCIO ncio;
    SUBCASE("CG2_8179")
    {
        const std::string fileName = NexusData::m_DataDirectory +
                                     "/data/nexus/hdf5/" + "CG2_8179.nxs.h5";
        ncio::DataDescriptor fr = ncio.Open(fileName, ncio::OpenMode::read);

        std::vector<std::uint64_t> bank_event_id;
        std::vector<std::uint64_t> bank_event_index;
        std::vector<float> bank_event_time_offset;
        std::vector<std::uint32_t> bank_event_time_zero;
        std::vector<std::uint64_t> bank_total_counts;

        std::chrono::milliseconds ncioTime(0);
        std::chrono::milliseconds h5dumpTime(0);

        for (std::size_t b = 1; b < 40; ++b)
        {
            auto t0 = std::chrono::high_resolution_clock::now();
            const std::string bankGroup =
                "/entry/bank" + std::to_string(b) + "_events/";

            const std::string entryEventID = bankGroup + "event_id";
            const std::string entryEventIndex = bankGroup + "event_index";
            const std::string entryEventTimeOffset =
                bankGroup + "event_time_offset";
            const std::string entryEventTimeZero =
                bankGroup + "event_time_zero";
            const std::string entryTotalCounts = bankGroup + "total_counts";

            fr.Get(entryEventID, bank_event_id, ncio::BoxAll);
            fr.Get(entryEventIndex, bank_event_index, ncio::BoxAll);
            fr.Get(entryEventTimeOffset, bank_event_time_offset, ncio::BoxAll);
            fr.Get(entryEventTimeZero, bank_event_time_zero, ncio::BoxAll);
            fr.Get(entryTotalCounts, bank_total_counts, ncio::BoxAll);
            fr.Execute();

            auto t1 = std::chrono::high_resolution_clock::now();

            // get expected daata from h5dump
            std::vector<std::uint64_t> expected_bank_event_id =
                m_ExpectedData.GetArray<std::uint64_t>(fileName, entryEventID);

            std::vector<std::uint64_t> expected_bank_event_index =
                m_ExpectedData.GetArray<std::uint64_t>(fileName,
                                                       entryEventIndex);

            std::vector<float> expected_bank_event_time_offset =
                m_ExpectedData.GetArray<float>(fileName, entryEventTimeOffset);

            std::vector<std::uint32_t> expected_bank_event_time_zero =
                m_ExpectedData.GetArray<std::uint32_t>(fileName,
                                                       entryEventTimeZero);

            std::vector<std::uint64_t> expected_bank_total_counts =
                m_ExpectedData.GetArray<std::uint64_t>(fileName,
                                                       entryTotalCounts);

            CHECK_EQ(bank_event_id, expected_bank_event_id);
            CHECK_EQ(bank_event_index, expected_bank_event_index);
            CHECK_EQ(bank_event_time_offset, expected_bank_event_time_offset);
            CHECK_EQ(bank_event_time_zero, expected_bank_event_time_zero);
            CHECK_EQ(bank_total_counts, expected_bank_total_counts);

            auto t2 = std::chrono::high_resolution_clock::now();

            ncioTime +=
                std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
            h5dumpTime +=
                std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        }

        fr.Close();

        std::cout << "NCIO time: " << ncioTime.count() << " ms";
        std::cout << "\n";
        std::cout << "h5dump time: " << h5dumpTime.count() << " ms";
        std::cout << "\n";
    }
}

TEST_CASE_FIXTURE(NexusData,
                  "Regression nightly tests for nexus HDF5 data index "
                  "DataDescriptor::GetMetadata cases")
{
    auto lf_CheckIndex = [&](ncio::NCIO &ncio, const std::string &fileName,
                             ncio::schema::nexus::model1_t &expectedIndex,
                             const bool generate = false) {
        ncio::DataDescriptor fr = ncio.Open(fileName, ncio::OpenMode::read);

        const auto index = fr.GetMetadata<ncio::schema::nexus::index::model1,
                                          ncio::schema::nexus::model1_t>();

        if (!generate)
        {
            CHECK_EQ(index, expectedIndex);
        }
        else // generate the json file for map<string,set<string>> NX_class
             // based index
        {
            nlohmann::json jsonIndex;

            for (const auto &indexPair : index)
            {
                const std::string &nxClass = indexPair.first;
                jsonIndex[nxClass] = nlohmann::json::array();

                for (const std::string &entry : indexPair.second)
                {
                    jsonIndex[nxClass].push_back(entry);
                }
            }

            std::ofstream o("pretty.json");
            o << std::setw(4) << jsonIndex << "\n";
            o.close();
        }

        fr.Close();
    };

    std::cout << "Nexus-Data location: " << NexusData::m_DataDirectory << "\n";

    std::map<std::string, ncio::schema::nexus::model1_t &> fileIndices = {
        {"CG2_8179.nxs", m_ExpectedIndex.CG2_8179},
        {"CG2_8953.nxs", m_ExpectedIndex.CG2_8953},
        {"CG3_1545.nxs", m_ExpectedIndex.CG3_1545},
        {"CG3_943.nxs", m_ExpectedIndex.CG3_943},
        {"EQSANS_112296.nxs", m_ExpectedIndex.EQSANS_112296},
        {"EQSANS_112307.nxs", m_ExpectedIndex.EQSANS_112307},
        {"NOM_78106.nxs", m_ExpectedIndex.NOM_7816}};

    const bool generate = true;

    ncio::NCIO ncio;

    for (const auto &fileIndexPair : fileIndices)
    {
        const std::string h5FileName =
            m_DataDirectory + "/data/nexus/hdf5/" + fileIndexPair.first + ".h5";
        const std::string index1FileName = m_DataDirectory +
                                           "/data/nexus/index1/" +
                                           fileIndexPair.first + ".json";

        // log the current input data file on doctest
        // in case of failure it would report which index
        CAPTURE(fileIndexPair.first);

        // generate the index in memory
        std::map<std::string, std::set<std::string>> &index =
            fileIndexPair.second;
        if (!generate)
        {
            m_ExpectedIndex.InitIndex(index1FileName, index);
        }

        lf_CheckIndex(ncio, h5FileName, index, generate);
    }
#endif
}

} // end namespace

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        throw std::logic_error(
            "Error: missing ncio-data location as first argument\n");
    }

    doctest::Context context(argc, argv);
    // make sure struct is set before context.run() as it's implicitly passed
    ncio::testing::regression::NexusData::m_DataDirectory =
        std::string(argv[1]);

    int result = context.run();

    return result;
}
