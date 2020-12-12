# MESON functional tests executables
#  Created on: May 19, 2020
#      Author: William F Godoy godoywf@ornl.gov


tests = ['NCIO', 'DataDescriptor']

foreach test : tests
  exe = executable('functionaltest-cxx17-' + test, 
                   'functionalTest_cxx17' + test + '.cpp',
                   include_directories:  ncio_doctest_inc, 
                   dependencies: [ncio_cxx17_dep, doctest_dep, threads_dep])
  test(test, exe, timeout: 10, suite: ['functionaltest', 'cxx17'], is_parallel: false )
endforeach


foreach ncio_schema : ncio_schemas
  
  test = ncio_schema.to_lower()
  file_name = 'schema' / test / 'functionalTest_cxx17DataDescriptor' + ncio_schema + '.cpp'
  
  exe = executable('functionaltest-cxx17-schema-' + test, 
                   file_name,
                   include_directories:  ncio_doctest_inc, 
                   dependencies: [ncio_cxx17_dep, doctest_dep, threads_dep])
  test( test, exe, timeout: 10, suite: ['functionaltest', 'cxx17', 'schema'])
endforeach