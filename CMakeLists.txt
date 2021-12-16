cmake_minimum_required(VERSION 3.14)

# set the project name
project(Emulator8086)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
enable_testing()

#add_compile_definitions(NDEBUG)



set($CMAKE_SOURCE_DIR .)


add_compile_options(-Wall)
add_compile_options(-g)
add_compile_options(-Wextra)
#add_compile_options(-fsanitize=undefined)

# add the executable
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib86)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/emulator)

add_custom_target(run COMMAND ninja &&./emulator/emulator
  USES_TERMINAL
  )

add_custom_target(gdb COMMAND ninja && gdb ./emulator/emulator
  USES_TERMINAL
  )




