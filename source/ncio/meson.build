# MESON libncio compilation and install common headers
#  Created on: May 11, 2020
#      Author: William F Godoy godoywf@ornl.gov

# EXPECT THIS TO GROW
ncio_sources = ['core/NCIO.cpp',
                'core/DataDescriptor.cpp']

ncio_inc = include_directories(['..'])
ncio_lib = library('ncio', 
                   sources: ncio_sources,
                   include_directories: ncio_inc,
                   install: true)

# CREATE A DEPENDENCY FOR BINDINGS and TESTS
# using '../' as headers are included from the upper-level ncio directory
ncio_dep = declare_dependency( link_with: ncio_lib, 
                               include_directories: ncio_inc )

# INSTALL COMMON PUBLIC HEADERS
install_headers('common/ncioMacros.h', subdir : 'ncio/common') 
install_headers('common/ncioTypes.h', subdir : 'ncio/common') 
install_headers('common/ncioTypesNexus.h', subdir: 'ncio/common')
