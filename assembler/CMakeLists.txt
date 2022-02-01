add_executable(assembler main.cpp)

#add_test(basic emulator ${CMAKE_SOURCE_DIR}/tests/test.com)

add_dependencies(
  assembler
  lib86
  )

target_include_directories(
  assembler
  PUBLIC ${CMAKE_SOURCE_DIR}/lib86
  )


target_link_libraries(
  assembler
  lib86
  )
target_link_libraries(
  assembler
  Qt5::Core
  )
