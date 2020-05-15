# MESON file to build the ncio-cxx17 bindings library
#  Created on: May 11, 2020
#      Author: William F Godoy godoywf@ornl.gov  


ncio_cxx17_src = ['ncio/cxx17/cxx17NCIO.cpp']
ncio_cxx17_inc = include_directories(['ncio/cxx17'])

ncio_cxx17_lib = library('ncio-cxx17', 
                         sources: ncio_cxx17_src,
                         include_directories: ncio_cxx17_inc,
                         dependencies : [ncio_dep],
                         install: true)

# installation headers
# only public header that should be included in projects using ncio
install_headers('ncio.h')

# other CXX17 headers 
headers_cxx17 = ['cxx17NCIO.h']

# meson is not Turing-complete, so user-defined functions are not possible
# list + loop is a great and clean workaround
# install in -> include/ncio/cxx17/header.h
foreach header_cxx17 : headers_cxx17
  install_headers('ncio/cxx17/'+header_cxx17, subdir:'ncio/cxx17')
endforeach
