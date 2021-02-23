#include "ncio-doctest.h"

#include <array>
#include <future>
#include <numeric> // std::iota
#include <thread>

#include <ncio.h>

TEST_CASE("Nightly tests for ncio::NCIO C++17 bindings class")
{
    ncio::NCIO ncio;

#ifdef NCIO_HAVE_HDF5
    SUBCASE("OpenHDF5")
    {
        ncio::DataDescriptor fw =
            ncio.Open("total_counts.h5", ncio::OpenMode::read);
    }

#endif
}
