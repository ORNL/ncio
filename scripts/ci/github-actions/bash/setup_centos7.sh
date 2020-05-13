#!/bin/bash

# Only updating, upgrading can be slow. Might create a new container in the future
yum update -y

# Get dependencies
# git 2.22.0
yum install http://opensource.wandisco.com/centos/7/git/x86_64/wandisco-git-release-7-2.noarch.rpm -y
yum install git -y

# ninja 1.8x
yum install http://repo.okay.com.mx/centos/7/x86_64/release/okay-release-1-1.noarch.rpm -y
yum install ninja-build  -y

# Get a more recen meson v0.54 from pip3
yum install python3-pip -y
pip3 install meson
