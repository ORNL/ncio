FROM centos:centos7
LABEL William F Godoy williamfgc@yahoo.com
LABEL Mark Abraham markabraham3232@gmail.com 

RUN set -x  \
  && echo "[SCL-core]"                                                                                         >> /etc/yum.repos.d/CentOS-Base.repo \
  && echo "name=Springdale SCL Base \$releasever - \$basearch"                                                  >> /etc/yum.repos.d/CentOS-Base.repo \
  && echo "mirrorlist=http://springdale.princeton.edu/data/springdale/SCL/\$releasever/\$basearch/mirrorlist"   >> /etc/yum.repos.d/CentOS-Base.repo \
  && echo "#baseurl=http://springdale.princeton.edu/data/springdale/SCL/\$releasever/\$basearch"                >> /etc/yum.repos.d/CentOS-Base.repo \
  && echo "gpgcheck=0"                                                                                        >> /etc/yum.repos.d/CentOS-Base.repo

RUN yum update -y &&\
    yum upgrade -y &&\
    cat /etc/yum.repos.d/CentOS-Base.repo &&\
    yum install centos-release-scl -y &&\
    yum install devtoolset-8-gcc devtoolset-8-gcc-c++ llvm-toolset-6.0 -y &&\
# git 2.x
    yum install http://opensource.wandisco.com/centos/7/git/x86_64/wandisco-git-release-7-2.noarch.rpm -y &&\
# ninja-build 8
    yum install http://repo.okay.com.mx/centos/7/x86_64/release/okay-release-1-1.noarch.rpm -y &&\
    yum install git git-lfs ninja-build python3-pip hdf5-devel pkg-config which -y &&\   
    pip3 install meson==0.56 &&\
# enable gcc and clang compilers
    echo "source scl_source enable devtoolset-8" >> ~/.bash_profile &&\
    echo "source scl_source enable llvm-toolset-6.0" >> ~/.bash_profile &&\
    source ~/.bash_profile