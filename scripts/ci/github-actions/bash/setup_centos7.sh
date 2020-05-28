#!/bin/bash

# Enable gcc and clang compilers
echo 'Enabling gcc and clang compilers on CentOS'
source scl_source enable devtoolset-8
source scl_source enable llvm-toolset-7
