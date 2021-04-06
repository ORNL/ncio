/**
 * nightlyTest_NexusData.cpp
 *
 *  Created on: Mar 25, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "nightlyTest_NexusData.h"
#include "nightlyTest_NexusData.tcc"

#include <fstream>

#include <nlohmann/json.hpp>

namespace ncio::testing::regression
{

std::string NexusData::m_DataDirectory = "";

void NexusData::ExpectedIndex::InitIndex(
    const std::string &fileName,
    std::map<std::string, std::set<std::string>> &index)
{
    // load index from json
    std::ifstream jsonFile(fileName);
    nlohmann::json json;
    jsonFile >> json;
    jsonFile.close();

    for (const auto &nxClassPair : json.items())
    {
        const std::string nxClass = nxClassPair.key();

        for (const auto &entry : json[nxClass])
        {
            index[nxClass].insert(entry.get<std::string>());
        }
    }
}

} // end namespace ncio::testing::regression
