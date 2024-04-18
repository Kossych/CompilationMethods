cmake_minimum_required(VERSION 3.29.0)
project(Parser)

add_library(parser src/parser.cpp lib/parser.h)

add_executable(test1 tests/test1.cpp)

target_link_libraries(test1 parser)