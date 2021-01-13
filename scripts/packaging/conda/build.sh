#!/bin/bash

# builds ncio for conda using default options and 
# a xeus-cling kernel https://github.com/jupyter-xeus/xeus-cling
# for usage with Jupyter C++ cling kernel 

set -e
set -x

mkdir build
cd build

meson --prefix=$PREFIX ..
ninja
ninja install

# Create a cling public header to be used in Jupyter Notebooks
CLING_HEADER=$PREFIX/include/ncio-cling.h

echo -e '#pragma cling add_library_path("'$PREFIX'/lib")' > $CLING_HEADER
echo -e '#pragma cling add_include_path("'$PREFIX'/include")' >> $CLING_HEADER
echo -e '#pragma cling load("ncio-cxx17")' >> $CLING_HEADER
echo -e '#include <ncio.h>' >> $CLING_HEADER
