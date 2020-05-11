

ncio_src = ['core/NCIO.cpp']
ncio_inc = include_directories(['common','core'])

ncio_lib = library('ncio', 
                   sources: ncio_src,
                   include_directories: ncio_inc,
                   install: true)

# creating a dependency to make it easy to integrate
# using '../' as headers are included from the ncio prefix
ncio_dep = declare_dependency( link_with: ncio_lib, 
                               include_directories: ['../'] )

# -> include/ncio/common/header.h
install_headers('common/ncioTypes.h', subdir : 'ncio/common') 
install_headers('common/ncioTypesNexus.h', subdir: 'ncio/common')
