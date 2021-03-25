# pre-compile data into a library
# indices can be large
sources_nexus_data = ['nightlyTest_nexusDataIndex_CG2_8179.cpp',
                      'nightlyTest_nexusDataIndex_CG2_8953.cpp',
                      'nightlyTest_nexusDataIndex_CG3_1545.cpp',
                      'nightlyTest_nexusDataIndex_CG3_943.cpp',
                      'nightlyTest_nexusDataIndex_EQSANS_112296.cpp',
                      'nightlyTest_nexusDataIndex_EQSANS_112307.cpp',
                      'nightlyTest_nexusDataIndex_NOM_78106.cpp'
                     ]

nexusindex_lib = library( 'nexus-index-data', 
                          sources: sources_nexus_data,
                          include_directories: include_directories('.'),
                          install: false)

# list of nightly tests for nexus schema
nightly_tests_nexus = [ 'nexusDataIndex' ]
foreach test: nightly_tests_nexus 
  file_name = 'nightlyTest_' + test + '.cpp'
  exe = executable('nightlytest-' + test, 
                     file_name,
                     include_directories:  ncio_doctest_inc,
                     link_with: nexusindex_lib, 
                     dependencies: [ncio_cxx17_dep, doctest_dep, ncio_data_dep, nlohmann_json_dep, threads_dep])
  
  ncio_data_dir = meson.source_root() / 'subprojects' / 'ncio-data'
  
  test(test, exe, args: [ncio_data_dir], timeout: 10, 
       suite: ['regression', 'nightlytest', 'nexus'] )
endforeach
