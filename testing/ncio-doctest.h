/*
 * ncio-doctest.h : common interface header, wrapper around doctest.h header to
 * add #define to all tests
 *
 *  Created on: May 11, 2020
 *      Author: William F Godoy godoywf@ornl.gov
 */

#pragma once

// Here we can add global #define options to doctest. For documentation see:
// https://github.com/onqtam/doctest/blob/master/doc/markdown/configuration.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_POSIX_SIGNALS

#include <doctest.h>
