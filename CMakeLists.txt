cmake_minimum_required(VERSION 3.23)
project(clickhouse_native_client_example)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib)

add_executable(clickhouse_native_client_example src/main.cpp)
