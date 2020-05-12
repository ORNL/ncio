# MESON build main file
#  Created on: May 11, 2020
#      Author: William F Godoy godoywf@ornl.gov

# Define project information
project('ncio',
        ['cpp'],
        license: 'BSD 3-Clause',
        version: '0.0.1',
        meson_version: '>=0.52.0',
        default_options: ['cpp_std=c++17', 'buildtype=debug', 'layout=flat']
)

# private ncio library
subdir('source')

# bindings depend on ncio library
subdir('bindings')

# tests
if get_option('build-tests')
  doctest_dep = dependency('doctest', fallback: ['doctest', 'doctest_dep'])
  subdir('testing')
endif
