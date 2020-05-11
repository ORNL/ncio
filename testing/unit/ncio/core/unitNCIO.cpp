/**
 * unitNCIO.cpp : unit tests for the core::NCIO class using the doctest
 * framework
 *
 *  Created on: May 11, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#include "ncio-doctest.h"

#include "ncio/core/NCIO.h"

TEST_CASE("Unit test for core::NCIO class")
{
    ncio::core::NCIO ncio;
    ncio.SetParameter("key", "value");
    SUBCASE("GetParameter") { REQUIRE(ncio.GetParameter("key") == "value"); }
    SUBCASE("GetConfigFile") { CHECK(ncio.m_ConfigFile == ""); }
}
