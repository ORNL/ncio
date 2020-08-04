#!/bin/bash

# Run specific steps based on input
if test -f /root/.bash_profile; then
  echo "Enabling gcc and clang compilers"	
  source /root/.bash_profile
  gcc --version
fi

case "$1" in 

  # Configure ncio using meson using out-of-source builds 
  configure)
    cd ${GITHUB_WORKSPACE}/..
    mkdir ncio-build
    cd ncio-build
    
    case "${GH_JOBNAME}" in
      # Sanitize with clang compilers
      *"asan"*)
        echo 'Configure for address sanitizer asan'
        CC=clang CXX=clang++ meson -Db_lundef=false -Db_sanitize=address --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      *"ubsan"*)
        echo 'Configure for undefined behavior sanitizer ubsan'
        CC=clang CXX=clang++ meson -Db_lundef=false -Db_sanitize=undefined --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      *"tsan"*)
        echo 'Configure for thread sanitizer tsan'
        CC=clang CXX=clang++ meson -Db_lundef=false -Db_sanitize=thread --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      *"msan"*)
        echo 'Configure for unintialized memory sanitizer msan'
        CC=clang CXX=clang++ meson -Db_lundef=false -Db_sanitize=memory --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      *"coverage"*)
        echo 'Configure for code coverage'
        apt-get update
        update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-8 800 && \
        apt-get install curl -y &&\
        pip3 install gcovr &&\
        meson -Dbuildtype=debugoptimized -Db_coverage=true --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      # Test with clang compilers
      *"clang"*)
        echo 'Configure for clang compilers'
        CC=clang CXX=clang++ meson --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      # Test with default compilers
      *)
        echo 'Configure for default system compilers'
        meson --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
    esac
   
    ;;

  # Build using ninja
  build)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja
    ;;

  # Run all tests
  test)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja test
    ;;

  # Install the library
  install)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja test
    ;;
  
  # Generate coverage reports
  coverage)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja test coverage-xml
    du -hs meson-logs/coverage.xml
    cat meson-logs/coverage.xml
    ;;
    
  *)
    echo " Invalid step" "$1"
    exit -1
    ;;
esac
