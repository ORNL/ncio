#!/bin/bash

# centos7-* only
if test -f /root/.bash_profile; then
  source /root/.bash_profile
fi

echo -e "\nCheck gcc and clang compilers\n"
gcc --version
clang --version
echo -e "\nCheck meson build\n"
meson --version

case "$1" in 

  # Configure ncio using meson using out-of-source builds
  # Downloads ncio-data with -Dbuild-tests-regression=true
  configure)
   
    cd ${GITHUB_WORKSPACE}/..
    mkdir ncio-build
    cd ncio-build
    
    case "${GH_JOBNAME}" in
      # Test with clang compilers
      *"clang"*)
        echo 'Configure for clang compilers'
        CC=clang CXX=clang++ meson -Dbuild-tests-regression=true ${GITHUB_WORKSPACE}
      ;;
      # Test with default compilers
      *)
        echo 'Configure for default system compilers'
        meson -Dbuild-tests-regression=true ${GITHUB_WORKSPACE}
      ;;
    esac
   
    ;;

  # Build using ninja
  build)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja
    ;;

  # Run all tests inclusing regression
  test)
    cd ${GITHUB_WORKSPACE}/../ncio-build
    ninja test
    ;;

  *)
    echo " Invalid step" "$1"
    exit -1
    ;;
esac
