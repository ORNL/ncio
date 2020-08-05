FROM ubuntu:18.04
MAINTAINER William F Godoy williamfgc@yahoo.com
RUN apt-get update -y &&\
    apt-get upgrade -y &&\
    DEBIAN_FRONTEND=noninteractive \
    apt-get install gcc-8 g++-8 dpkg-dev libc6-dev libc-dev make \
                    clang \
                    pkg-config \
                    python3-pip \
                    git \
                    ninja-build \
                    libhdf5-serial-dev \
                    curl \
                    -y &&\
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8 &&\
    update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-8 800 &&\
    pip3 install gcovr &&\
    pip3 install meson
