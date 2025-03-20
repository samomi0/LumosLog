cmake_minimum_required(VERSION 3.20)
project(LumosLog)

set(CMAKE_CXX_STANDARD 20)

find_package(spdlog REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

# demo
add_executable(demo example/demo.cpp)
target_link_libraries(demo spdlog::spdlog)

