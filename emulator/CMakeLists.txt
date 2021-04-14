add_executable(emulator main.cpp)

add_dependencies(
  emulator
  lib86
  )

target_include_directories(
  emulator
  PUBLIC ${CMAKE_SOURCE_DIR}/lib86
  )


target_link_libraries(
  emulator
  lib86
  )


