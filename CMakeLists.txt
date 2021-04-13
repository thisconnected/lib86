cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS OFF)

# set the project name
project(Emulator8086)

set($CMAKE_SOURCE_DIR .)

# add the executable
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib86)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/emulator)

add_custom_target(run COMMAND ./emulator/emulator
  USES_TERMINAL
  )

set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")

add_compile_options(-Wall)
add_compile_options(-Wextra)
