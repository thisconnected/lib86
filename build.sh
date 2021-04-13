#!/bin/sh
set -o errexit

rm -rf build
mkdir build
cd build
cmake ..
cmake --build .  --target emulator
./emulator/emulator

set +o errexit
