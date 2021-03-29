

#include "nightlyTest_NexusData.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

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

        std::vector<std::uint64_t> event_id(1000);

        fr.Get<ncio::schema::nexus::entry::bank1_events::event_id>(
            event_id.data(), ncio::BoxAll);
        fr.Execute();

        //        std::vector<std::uint64_t> expected_event_id =
        //            testInfo::expectedData::GetArray<std::uint64_t>(
        //                fileName, "/entry/bank1_events/event_id");

        fr.Close();
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
