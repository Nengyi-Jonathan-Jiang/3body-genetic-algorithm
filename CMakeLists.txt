cmake_minimum_required(VERSION 3.24)
project(3body_genetic_algorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(3body_genetic_algorithm
        src/wasm/3body.cpp)
