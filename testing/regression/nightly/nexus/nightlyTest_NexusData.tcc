/**
 * nightlyTest_nexusDataIndex.tcc
 *
 *  Created on: Mar 9, 2021
 *      Author: William F Godoy godoywf@ornl.gov
 */
#pragma once

#include "nightlyTest_NexusData.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace ncio::testing::regression
{

template <class T>
std::vector<T>
NexusData::ExpectedData::GetArray(const std::string &hdf5FileName,
                                  const std::string &arrayDataset)
{
    const std::string h5dumpCommand =
        "h5dump -y -d " + arrayDataset + " " + hdf5FileName + " > temp.dat";

    int status = std::system(h5dumpCommand.c_str());
    if (status)
    {
        throw std::runtime_error(
            "ncio ERROR test: could not run h5dump on file " + hdf5FileName +
            "\n");
    }

    // advance "nrecords"
    auto lf_Advance = [](std::ifstream &stream, const std::size_t nrecords) {
        std::string record;
        for (std::size_t r = 0; r < nrecords; ++r)
        {
            stream >> record;
        }
    };

    std::ifstream fdump("temp.dat");
    std::string record;

    //    HDF5 "CG3_1003.nxs.h5" {
    //    DATASET "/entry/instrument/bank1/event_id" {
    //       DATATYPE  H5T_STD_U32LE
    //       DATASPACE  SIMPLE { ( 1733 ) / ( H5S_UNLIMITED ) }
    //       DATA {
    //          171,
    lf_Advance(fdump, 12);
    fdump >> record;

    // only 1D in NeXus data
    const std::size_t nx = std::stoull(record);
    std::vector<T> data;
    data.reserve(nx);

    lf_Advance(fdump, 8);

    for (std::size_t i = 0; i < nx; ++i)
    {
        std::string datumString;
        std::getline(fdump, datumString, ',');
        std::istringstream datumSS(datumString);
        T datum;
        datumSS >> datum;
        data.push_back(datum);
    }

    return data;
}

template std::vector<std::uint32_t>
NexusData::ExpectedData::GetArray<std::uint32_t>(const std::string &,
                                                 const std::string &);

template std::vector<std::uint64_t>
NexusData::ExpectedData::GetArray<std::uint64_t>(const std::string &,
                                                 const std::string &);

template std::vector<float>
NexusData::ExpectedData::GetArray<float>(const std::string &,
                                         const std::string &);

} // end namespace
