
# key: suite, value: list of tests
unit_tests = { 'core' : ['NCIO'], 
               'helper' : ['ncioHelperString']
             }

foreach key, value: unit_tests
  
  suite = key

  foreach test: value
    file_name = 'ncio' / suite / 'unitTest_' + test + '.cpp'
     
    exe = executable('unittest-' + suite + '-' + test, 
                     file_name,
                     include_directories:  ncio_doctest_inc, 
                     dependencies: [ncio_dep, doctest_dep])
    test(test, exe, timeout: 10, suite: ['unittest', suite] )
   
  endforeach
   
endforeach
