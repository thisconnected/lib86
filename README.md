# Emulator 8086

![Build](https://github.com/thisconnected/pracainzynierska/actions/workflows/cmake.yml/badge.svg)

Emulator for Intel 8086 processor

## About

This emulator is project for my upcoming Bachelor's thesis

## Features

## Building

### Linux Prerequisites

Ubuntu 20.04
```console
sudo apt install g++ cmake ninja
```

### Linux Building

Either use `./build.sh` script or

```console
mkdir build
cd build/
cmake .. -G Ninja #or your favorite build system

#actually build
ninja

#and run
ninja run
```

