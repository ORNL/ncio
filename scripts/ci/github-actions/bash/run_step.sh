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
      # Test with clang compilers
      *"clang"*)
        CC=clang CXX=clang++ meson --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
      ;;
      # Test with default compilers
      *)
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

  *)
    echo " Invalid step" "$1"
    exit -1
    ;;
esac
