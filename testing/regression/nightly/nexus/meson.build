
# indices can be large, put them in json files

# list of nightly tests files for nexus schema
nightly_tests_nexus = [ 'NexusDataTests' ]
foreach test: nightly_tests_nexus 
  file_name = 'nightlyTest_' + test + '.cpp'
  exe = executable('nightlytest-' + test, 
                     [ file_name, 'nightlyTest_NexusData.cpp'],
                     include_directories:  ncio_doctest_inc,
                     dependencies: [ncio_cxx17_dep, doctest_dep, ncio_data_dep, nlohmann_json_dep, threads_dep])
  
  ncio_data_dir = meson.source_root() / 'subprojects' / 'ncio-data'
  
  # longer tests, timeout must be one minute or larger
  test(test, exe, args: [ncio_data_dir], timeout: 1000, 
       suite: ['regression', 'nightlytest', 'nexus'] )
endforeach
