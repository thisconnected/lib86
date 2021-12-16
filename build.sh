#!/bin/sh
set -o errexit

rm -rf build
mkdir build
cd build
cmake .. -G Ninja
ninja
ctest --output-on-failure

set +o errexit
