

#include "nightlyTest_nexusDataIndex.h"
#include "nightlyTest_nexusDataIndex.tcc"

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

#include <iostream>
#include <stdexcept>
#include <string>

#include <ncio.h>

namespace ncio::testing::regression
{

// initialize "global"
std::string testInfo::ncioDataDir = "";

#ifdef NCIO_HAVE_HDF5
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
        else // generate the map<string,set<string>> NX_class based index
        {
            std::cout << "{ ";

            for (const auto &indexPair : index)
            {
                std::cout << "{ \"" << indexPair.first << "\", {";

                for (const auto &entry : indexPair.second)
                {
                    std::cout << "\"" << entry << "\", ";
                }
                std::cout << "} }, ";
            }
            std::cout << "};";
        }

        fr.Close();
    };

    std::cout << "Nexus-Data location: " << testInfo::ncioDataDir << "\n";

    const std::map<std::string, const ncio::schema::nexus::model1_t &>
        fileIndices = {
            {"CG2_8179.nxs.h5", testInfo::expectedIndex::CG2_8179},
            {"CG2_8953.nxs.h5", testInfo::expectedIndex::CG2_8953},
            {"CG3_1545.nxs.h5", testInfo::expectedIndex::CG3_1545},
            {"CG3_943.nxs.h5", testInfo::expectedIndex::CG3_943},
            {"EQSANS_112296.nxs.h5", testInfo::expectedIndex::EQSANS_112296},
            {"EQSANS_112307.nxs.h5", testInfo::expectedIndex::EQSANS_112307},
            {"NOM_78106.nxs.h5", testInfo::expectedIndex::NOM_7816}};

    ncio::NCIO ncio;

    for (const auto &fileIndexPair : fileIndices)
    {
        const std::string fileName =
            testInfo::ncioDataDir + "/data/nexus/hdf5/" + fileIndexPair.first;

        // log the current input data file on doctest
        CAPTURE(fileName);
        lf_CheckIndex(ncio, fileName, fileIndexPair.second);
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
