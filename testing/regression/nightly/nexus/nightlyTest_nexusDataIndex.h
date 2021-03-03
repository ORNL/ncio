/*
 * nightlyTest_nexusDataIndex.h
 *
 *  Created on: Mar 2, 2021
 *      Author: wgodoy
 */

#pragma once

#include <map>
#include <set>
#include <string>

namespace ncio::testing::regression
{

/**
 * Contains test data info for validation. Can be passed to
 * doctest's TEST_CASE_FIXTURE
 */
struct testInfo
{
    static std::string ncioDataDir;
    const static std::map<std::string, std::set<std::string> >
        expectedIndexNOM_7816;
    const static std::map<std::string, std::set<std::string> >
        expectedIndexCG2_8179;
    const static std::map<std::string, std::set<std::string> >
        expectedIndexCG2_8953;
    const static std::map<std::string, std::set<std::string> >
        expectedIndexCG3_1545;
    const static std::map<std::string, std::set<std::string> >
        expectedIndexCG3_943;
    const static std::map<std::string, std::set<std::string> >
        expectedIndexEQSANS_112296;
    const static std::map<std::string, std::set<std::string> >
        expectedIndexEQSANS_112307;
};

}
