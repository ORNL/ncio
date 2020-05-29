# MESON private libncio configuration and installation of common headers
#  Created on: May 11, 2020
#      Author: William F Godoy godoywf@ornl.gov

# EXPECT THIS TO GROW
ncio_sources = ['core/NCIO.cpp',
                'core/DataDescriptor.cpp',
                
                'transport/Transport.cpp',
                'transport/TransportNull.cpp',
                
                'schema/ncioNexus.cpp']

# OPTIONAL EXTERNAL DEPENDENCIES SOURCES 
if hdf5_dep.found()
  ncio_sources += ['transport/TransportHDF5.cpp']  
endif

ncio_inc = include_directories(['..'])

ncio_lib = library('ncio', 
                   sources: ncio_sources,
                   include_directories: ncio_inc,
                   install: true, 
                   dependencies: ncio_dependencies)

# CREATE A DEPENDENCY FOR BINDINGS and TESTS
# using '../' as headers are included from the upper-level ncio directory
ncio_dep = declare_dependency( link_with: ncio_lib, 
                               include_directories: ncio_inc )

# CONFIGURATION FILE ncioConfig.h from ncioConfig,h.in
config_data = configuration_data()
# using semver 2.0 versioning https://semver.org/
version = meson.project_version()
config_data.set('NCIO_VERSION', version)
version_array = version.split('.')
config_data.set('NCIO_VERSION_MAJOR', version_array[0])
config_data.set('NCIO_VERSION_MINOR', version_array[1])
config_data.set('NCIO_VERSION_PATCH', version_array[2])
config_data.set('NCIO_VERSION_LICENSE', meson.project_license()[0] )

config_data.set('MESON_VERSION', meson.version() )
ncio_compiler = meson.get_compiler('cpp')
config_data.set('NCIO_CXX_COMPILER', ncio_compiler.get_id() )
config_data.set('NCIO_CXX_COMPILER_VERSION', ncio_compiler.version() )
config_data.set('NCIO_BUILD_TYPE', get_option('buildtype') )

config_data.set('NCIO_BUILD_SYSTEM', build_machine.system() )
config_data.set('NCIO_BUILD_CPU_INFO', build_machine.cpu() )
config_data.set('NCIO_BUILD_ENDIANNESS', build_machine.endian() )

if hdf5_dep.found()
  config_data.set('NCIO_HAVE_HDF5', true )
else
  config_data.set('NCIO_HAVE_HDF5', false )
endif

ncio_config_header = configure_file(input:  'common/ncioConfig.h.in',
                                    output: 'ncioConfig.h',
                                    configuration: config_data)

ncio_common_headers=['common/ncioTypes.h', 
                     'common/ncioTypesNexus.h']                
ncio_common_headers += ncio_config_header
# INSTALL COMMON PUBLIC HEADERS
install_headers(ncio_common_headers, subdir : 'ncio/common') 
