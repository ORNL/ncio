#!/bin/bash

# Run specific steps based on input

case "$1" in 

  # Configure ncio using meson using out-of-source builds 
  configure)
    cd ${GITHUB_WORKSPACE}/..
    mkdir ncio-build
    cd ncio-build
    meson --prefix=${GITHUB_WORKSPACE}/../ncio-install ${GITHUB_WORKSPACE}
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

  # Install the library (
  install)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja test
    ;;

  *)
    echo " Invalid step" "$1"
    exit -1
    ;;
esac
