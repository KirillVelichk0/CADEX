cmake_minimum_required(VERSION 3.20)
project(CAD_project)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
enable_testing()
add_library(CAD_lib SHARED CAD_lib/CAD_lib.h CAD_lib/CAD_lib.cpp)

add_executable(main main.cpp)
target_link_libraries(main CAD_lib)
add_executable(SimpleTests tests/main.cpp)
target_link_libraries(SimpleTests CAD_lib)
add_test(
  NAME test1
  COMMAND $<TARGET_FILE:SimpleTests>
  )
