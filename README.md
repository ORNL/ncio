# ncio
Neutrons Common Input Output, SNS/HFIR neutrons data management framework


## Installing from source with [Meson](https://mesonbuild.com/)

1. Requirements:

    - meson build >= 0.52.0, from `pip3 install meson` 
    - ninja
    - mono-complete (might be already installed on Ubuntu 18, 20, or macOS)

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

    
## Directory layout
* bindings - Public application programming interface, API, language bindings (C++17)

* scripts - Project maintenance and development scripts

* source - Internal source code for private components and public common headers to be installed
    * ncio - source directory for the ncio library to be installed as prefix/lib/libncio.*  

* testing - Tests unit and functional using [doctest](https://github.com/onqtam/doctest)
