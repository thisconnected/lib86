#!/bin/sh
set -o errexit

rm -rf build
mkdir build
cd build
cmake .. -G Ninja
ninja
ninja run

set +o errexit
