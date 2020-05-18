# MESON functional tests executables
#  Created on: May 19, 2020
#      Author: William F Godoy godoywf@ornl.gov

functional_tests = ['cxx17Common.cpp',
                    'cxx17NCIO.cpp']

foreach functional_test : functional_tests
  exe = executable('functionaltest-ncio-'+functional_test, 
                   'test_' + functional_test,
                   include_directories:  ncio_doctest_inc, 
                   dependencies: [ncio_cxx17_dep, doctest_dep])
  test(functional_test, exe, timeout: 10)
endforeach
