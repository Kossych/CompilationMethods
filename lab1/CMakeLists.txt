cmake_minimum_required(VERSION 3.29.0)
project(Analyzer)

add_library(analyzer src/analyzer.cpp lib/analyzer.h)

add_executable(test1 tests/test1.cpp)
add_executable(test2 tests/test2.cpp)

target_link_libraries(test1 analyzer)
target_link_libraries(test2 analyzer)