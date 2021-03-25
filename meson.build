# meson build main file
#  Created on: May 11, 2020
#      Author: William F Godoy godoywf@ornl.gov

# Define project information
project('ncio',
        ['cpp', 'c'],
        license: 'BSD 3-Clause',
        version: '0.0.1',
        meson_version: '>=0.52.0',
        default_options: ['cpp_std=c++17', 'buildtype=debugoptimized', 'layout=flat']
)

# SCHEMAS
# Supported schemas for compile time checks
ncio_supported_schemas = ['Nexus']
ncio_schemas = []
foreach ncio_supported_schema : ncio_supported_schemas 
  if get_option('NCIO_USE_SCHEMA_'+ ncio_supported_schema.to_upper())
    ncio_schemas += [ncio_supported_schema]
  endif
endforeach

# DEPENDENCIES
# Private external dependencies to ncio
ncio_dependencies = []
threads_dep = dependency('threads', 
                         required: true)
ncio_dependencies += [threads_dep]

hdf5_dep = dependency('hdf5',
                      language: 'c',
                      required: false,
                      static: false,
                      not_found_message: 'ncio dependency HDF5 not found')

if hdf5_dep.found()
  ncio_dependencies += [hdf5_dep]
endif

# Private ncio library
subdir('source')

# Public bindings which depend on private ncio library
subdir('bindings')

# Tests
if get_option('build-tests')
  doctest_dep = dependency('doctest', fallback: ['doctest', 'doctest_dep'])
  
  if get_option('build-tests-regression')
    ncio_data_dep = dependency('ncio-data', fallback: ['ncio-data', 'ncio_data_dep'])
    nlohmann_json_dep = dependency('nlohmann_json', fallback: ['nlohmann_json', 'nlohmann_json_dep'])
  endif
  
  subdir('testing')
endif

# Packaging
# pkg-config generation
# Meson uses pkg-config for library consumption.
# This module sets libraries (private and public) to link against
# pkg-config is supported by CMake based products
pkg = import('pkgconfig')
pkg.generate(libraries : ncio_cxx17_lib,
             version : '0.0.1',
             filebase : 'ncio',
             name : 'ncio',
             description : 'ncio library')
