# NeXus files Tests

NeXus regression tests for reading actual instrument data.

doctest based tests using an argument to the executable are located here:

- nightlyTest_nexusDataIndex.h
- nightlyTest_nexusDataIndex.cpp

In your `build` directory after compiling:
- To run all tests: `meson test`
- To run each test for debugging: `./meson-out/nightlytest-nexusDataIndex ~/workspace/ncio/subprojects/ncio-dat`

Each `nigthlyTest_nexusDataInde_*.cpp` will have the pre-stored expected NX_class index.
Actual files are not hosted by ncio, but using the external git lfs [ncio-data](https://code.ornl.gov/wfg/ncio-data.git) repo downloaded under `ncio/subprojects`, see [meson subprojects](https://mesonbuild.com/Subprojects.html), if regression is configured with `-Dbuild-tests-regression=true`.
