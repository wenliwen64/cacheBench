cmake_minimum_required(VERSION 3.10)

project(linagcpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(benchmark REQUIRED)
add_executable(Test main.cpp)
add_executable(BENCHMARK benchmark.cpp)
target_link_libraries(BENCHMARK benchmark::benchmark)