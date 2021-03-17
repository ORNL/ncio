/*
 * nightlyTest_nexusDataIndex.h
 *
 *  Created on: Mar 2, 2021
 *      Author: wgodoy
 */

#pragma once

#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <utility> // std::pair
#include <vector>

namespace ncio::testing::regression
{

/**
 * Contains test data info for validation. Can be passed to
 * doctest's TEST_CASE_FIXTURE
 */
struct testInfo
{
    static std::string ncioDataDir;

    /**
     * Holds a few array data for the each NeXus file. Runtime built with
     * h5dump from ncio/source/helper/ncioHelper/ncioHelperH5Dump*
     */
    struct expectedData
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

    /** Holds the expected index (at compile time) for the each NeXus file */
    struct expectedIndex
    {
        const static std::map<std::string, std::set<std::string>> CG2_8179;
        const static std::map<std::string, std::set<std::string>> CG2_8953;
        const static std::map<std::string, std::set<std::string>> CG3_1545;
        const static std::map<std::string, std::set<std::string>> CG3_943;
        const static std::map<std::string, std::set<std::string>> EQSANS_112296;
        const static std::map<std::string, std::set<std::string>> EQSANS_112307;
        const static std::map<std::string, std::set<std::string>> NOM_7816;
    };
};

} // end namespace
