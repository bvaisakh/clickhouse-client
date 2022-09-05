cmake_minimum_required(VERSION 3.23)
project(clickhouse_client)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
include_directories(lib/clickhouse-cpp)
include_directories(lib/clickhouse-cpp/contrib)

add_executable(
        clickhouse_client
        src/main.cpp
)
target_link_libraries(
        clickhouse_client
        clickhouse-cpp-lib-static
        absl-lib
)