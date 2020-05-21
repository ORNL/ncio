
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

# setup configuration file ncioConfig.h from ncioConfig,h.input
# using semver 2.0 versioning https://semver.org/                              
config_data = configuration_data()
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

ncio_config_header = configure_file(input:  'common/ncioConfig.h.in',
                                    output: 'ncioConfig.h',
                                    configuration: config_data)

ncio_common_headers=['common/ncioTypes.h', 
                     'common/ncioTypesNexus.h']                
ncio_common_headers += ncio_config_header

# -> include/ncio/common/header.h
install_headers(ncio_common_headers, subdir : 'ncio/common') 
