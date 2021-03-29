/**
 * nightlyTest_nexusData.h : define testInfo data object that holds regression
 * data from NeXus files
 *
 *  Created on: Mar 25, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace ncio::testing::regression
{

class NexusData
{
public:
    /** data directory for the nexus files, typically passed as a first
     * argument*/
    static std::string m_DataDirectory;

    /**
     * Holds a few array data for the each NeXus file. Runtime built with
     * h5dump from ncio/source/helper/ncioHelper/ncioHelperH5Dump*
     */
    struct ExpectedData
    {
        struct CG2_8179
        {
            std::vector<std::uint32_t> bank_event_id;
            std::vector<std::uint64_t> bank_event_index;
            std::vector<float> bank_event_time_offset;
            std::vector<std::uint32_t> bank_event_time_zero;
            std::vector<std::uint64_t> bank_total_counts;
        };
        // TODO expand to other files

        template <class T>
        static std::vector<T> GetArray(const std::string &hdf5FileName,
                                       const std::string &arrayDataset);
    };

    ExpectedData m_ExpectedData;

    /** Holds the expected index (at compile time) for the each NeXus file */
    struct ExpectedIndex
    {
        std::map<std::string, std::set<std::string>> CG2_8179;
        std::map<std::string, std::set<std::string>> CG2_8953;
        std::map<std::string, std::set<std::string>> CG3_1545;
        std::map<std::string, std::set<std::string>> CG3_943;
        std::map<std::string, std::set<std::string>> EQSANS_112296;
        std::map<std::string, std::set<std::string>> EQSANS_112307;
        std::map<std::string, std::set<std::string>> NOM_7816;

        void InitIndex(const std::string &fileName,
                       std::map<std::string, std::set<std::string>> &index);
    };

    ExpectedIndex m_ExpectedIndex;
};

} // end namespace
