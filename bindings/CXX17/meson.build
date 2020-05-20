# MESON file to build the ncio-cxx17 bindings library and public headers
#  Created on: May 11, 2020
#      Author: William F Godoy godoywf@ornl.gov  

ncio_cxx17_names = ['NCIO',
                    'DataDescriptor']

# meson is not Turing-complete, so user-defined functions are not possible
# list += loop is a great and clean workaround
ncio_cxx17_sources = []
foreach ncio_cxx17_name : ncio_cxx17_names
  ncio_cxx17_sources += ['ncio/cxx17/cxx17' + ncio_cxx17_name + '.cpp']
endforeach

# DEFINE LIBRARY
ncio_cxx17_lib = library('ncio-cxx17', 
                         sources: ncio_cxx17_sources,
                         include_directories: include_directories(['ncio/cxx17','../../source']),
                         dependencies : [ncio_dep],
                         install: true)

# public include current headers location for linking externally with tests
# and source for common headers
ncio_cxx17_dep = declare_dependency(link_with: ncio_cxx17_lib, 
                                    include_directories: ['.','../../source'])
                                    
# INSTALL PUBLIC HEADERS

# only public header that should be included in projects using ncio
install_headers('ncio.h')

# ncio/cxx17 headers 
# install in -> include/ncio/cxx17/cxx17.h
foreach ncio_cxx17_name : ncio_cxx17_names
  install_headers('ncio/cxx17/cxx17'+ncio_cxx17_name+'.h', subdir:'ncio/cxx17')
endforeach
