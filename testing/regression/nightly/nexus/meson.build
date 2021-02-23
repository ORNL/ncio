
# list of nightly tests for nexus schema
nightly_tests_nexus = [ 'nexusDataIndex' ]

foreach test: nightly_tests_nexus 
  file_name = 'nightlyTest_' + test + '.cpp'
  exe = executable('nightlytest-' + test, 
                     file_name,
                     include_directories:  ncio_doctest_inc, 
                     dependencies: [ncio_cxx17_dep, doctest_dep, ncio_data_dep, threads_dep])
  test(test, exe, timeout: 10, suite: ['regression', 'nightlytest', 'nexus'] )
endforeach
