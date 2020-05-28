FROM centos:centos7
MAINTAINER William F Godoy williamfgc@yahoo.com
RUN yum update -y &&\
    yum upgrade -y &&\
    yum install centos-release-scl -y &&\
    yum install devtoolset-8-gcc devtoolset-8-gcc-c++ llvm-toolset-7 -y &&\
# git 2.x
    yum install http://opensource.wandisco.com/centos/7/git/x86_64/wandisco-git-release-7-2.noarch.rpm -y &&\
# ninja-build 8
    yum install http://repo.okay.com.mx/centos/7/x86_64/release/okay-release-1-1.noarch.rpm -y &&\
    yum install git ninja-build python3-pip hdf5-devel which -y &&\   
    pip3 install meson &&\
    scl enable devtoolset-8 -- bash &&\
    scl enable llvm-toolset-7 bash
