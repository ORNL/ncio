# MESON unit tests executables
#  Created on: May 11, 2020
#      Author: William F Godoy godoywf@ornl.gov

unit_tests = ['unitTest_NCIO.cpp']

foreach unit_test : unit_tests
  exe = executable('unittest-ncio-core-NCIO', 
                   'ncio/core/' + unit_test,
                   include_directories:  ncio_doctest_inc, 
                   dependencies: [ncio_dep, doctest_dep])
  test(unit_test, exe, timeout: 10)
endforeach
