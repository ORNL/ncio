

#include "nightlyTest_nexusDataIndex.h"
#include "nightlyTest_nexusDataIndex.tcc"

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

#include <iostream>
#include <stdexcept>
#include <string>

#include <ncio.h>

#include <nlohmann/json.hpp>

namespace ncio::testing::regression
{

// initialize "global"
std::string testInfo::ncioDataDir = "";

#ifdef NCIO_HAVE_HDF5
TEST_CASE_FIXTURE(testInfo, "Regression nightly tests for nexus HDF5 data")
{
    ncio::NCIO ncio;
    SUBCASE("CG2_8179")
    {
        const std::string fileName =
            testInfo::ncioDataDir + "/data/nexus/hdf5/" + "CG2_8179.nxs.h5";
        ncio::DataDescriptor fr = ncio.Open(fileName, ncio::OpenMode::read);

        std::vector<std::uint64_t> event_id(1000);

        fr.Get<ncio::schema::nexus::entry::bank1_events::event_id>(
            event_id.data(), ncio::BoxAll);
        fr.Execute();

        std::vector<std::uint64_t> expected_event_id =
            testInfo::expectedData::GetArray<std::uint64_t>(
                fileName, "/entry/bank1_events/event_id");

        fr.Close();
    }
}

TEST_CASE_FIXTURE(testInfo,
                  "Regression nightly tests for nexus HDF5 data index "
                  "DataDescriptor::GetMetadata cases")
{
    auto lf_CheckIndex = [](ncio::NCIO &ncio, const std::string &fileName,
                            const ncio::schema::nexus::model1_t &expectedIndex,
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

    std::cout << "Nexus-Data location: " << testInfo::ncioDataDir << "\n";

    const std::map<std::string, const ncio::schema::nexus::model1_t &>
        fileIndices = {{"NOM_78106.nxs.h5", testInfo::expectedIndex::NOM_7816}};

    ncio::NCIO ncio;

    for (const auto &fileIndexPair : fileIndices)
    {
        const std::string fileName =
            testInfo::ncioDataDir + "/data/nexus/hdf5/" + fileIndexPair.first;

        // log the current input data file on doctest
        CAPTURE(fileName);
        lf_CheckIndex(ncio, fileName, fileIndexPair.second, true);
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
    ncio::testing::regression::testInfo::ncioDataDir = std::string(argv[1]);

    int result = context.run();

    return result;
}
