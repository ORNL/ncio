
# key: suite, value: list of tests
unit_tests = { 'core' : ['NCIO'], 
               'helper' : ['ncioHelperString']
             }

foreach key, value: unit_tests
  
  minisuite = key

  foreach test: value
    file_name = 'ncio' / minisuite / 'unitTest_' + test + '.cpp'
     
    exe = executable('unittest-' + minisuite + '-' + test, 
                     file_name,
                     include_directories:  ncio_doctest_inc, 
                     dependencies: [ncio_dep, doctest_dep])
    test(test, exe, timeout: 10, suite: ['ci','unittest', minisuite] )
   
  endforeach
   
endforeach
