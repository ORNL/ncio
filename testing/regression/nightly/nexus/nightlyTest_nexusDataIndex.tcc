/**
 * nightlyTest_nexusDataIndex.tcc
 *
 *  Created on: Mar 9, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */
#pragma once

#include "nightlyTest_nexusDataIndex.h"

#include <fstream>

namespace ncio::testing::regression
{

template <class T>
std::vector<T> testInfo::expectedData::GetArray(const std::string &hdf5FileName,
                                                const std::string &arrayDataset)
{
    const std::string h5dumpCommand =
        "h5dump -y -d " + arrayDataset + " " + hdf5FileName + " > temp.dat";
    std::system(h5dumpCommand.c_str());

    std::ifstream fdump("temp.dat");
    std::string record;
    for (std::size_t i = 0; i < 13; ++i)
    {
        fdump >> record;
    }
}

} // end namespace
