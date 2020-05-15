#!/bin/bash

# Only updating, upgrading can be slow. Might create a new container in the future
apt-get update

# Get dependencies
apt-get install ninja-build python3-pip python3-setuptools -y

# Get a more recen meson v0.54 from pip3
pip3 install meson
