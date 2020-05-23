[![Actions Status](https://github.com/ORNL/ncio/workflows/.github/workflows/GitHub%20Actions/badge.svg)](https://github.com/ORNL/ncio/actions)

# ncio
Neutrons Common Input Output, SNS/HFIR neutrons data management framework


## Installing ncio from source with [Meson](https://mesonbuild.com/)

1. Requirements:

    - meson build >= 0.52.0, from `pip3 install meson` 
    - ninja
    - mono-complete (might be already installed on Ubuntu 18, 20, or macOS)
    - pkg-config

2. Build, Test, Install:

    We highly recommend truly out-of-source builds (completely outside the repo directory).

    ```
    $ mkdir ncio-build
    $ cd ncio-build
    $ meson --prefix=/path/to/install/ncio  /path/to/repo/ncio
    $ ninja
    $ ninja test
    $ ninja install
    ```
    
3. Code coverage from tests (requires gcov)

   Meson can generate code coverage reports automatically from tests. 
   Requires passing `-Db_coverage=true` when configuring and running the `coverage` target.
   Reports would be generated under the `meson-logs` directory 

    ```
    $ mkdir ncio-build
    $ cd ncio-build
    $ meson --prefix=/path/to/install/ncio -Db_coverage=true /path/to/repo/ncio
    $ ninja 
    $ ninja coverage
    [1/1] Generates coverage reports
	lines: 45.8% (11 out of 24)
	branches: 34.6% (9 out of 26)

	Xml coverage report can be found at file:///Users/wfg/workspace/ncio-build/meson-logs/coverage.xml
	Text coverage report can be found at file:///Users/wfg/workspace/ncio-build/meson-logs/coverage.txt
	Html coverage report can be found at file:///Users/wfg/workspace/ncio-build/meson-logs/coveragereport/index.html
	```

## Linking ncio with CMake projects

Meson uses `pkg-config` as a standard packaging configuration method. 
Make sure ncio installation directory is reachable, so pc configuration files can be found. 
One of the methods is to pass `-DCMAKE_PREFIX_PATH=/installation/to/ncio` at configuration.
ncio can be easily be integrated with `CMake` projects via the [FindPkgConfig](https://cmake.org/cmake/help/latest/module/FindPkgConfig.html) module.
The following snippet illustrates how to create a ncio target and link it to a `CMake` target.
	
	```
	# find pkg-config
	find_package(PkgConfig REQUIRED) 
	# create target `PkgConfig::ncio`
	pkg_check_modules(ncio REQUIRED IMPORTED_TARGET ncio)
	# create a CMake target (_e.g._ executable)
	add_executable(ncio_cmake ncio_cmake.cpp)
	# link with PkgConfig::ncio target
	target_link_libraries(ncio_cmake PUBLIC PkgConfig::ncio)
	
	```

## Directory layout
* bindings - Public application programming interface, API, language bindings (C++17)

* scripts - Project maintenance and development scripts

* source - Internal source code for private components and public common headers to be installed
    * ncio - source directory for the ncio library to be installed as prefix/lib/libncio.*  

* testing - Tests unit and functional using [doctest](https://github.com/onqtam/doctest)
