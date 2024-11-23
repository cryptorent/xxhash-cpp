cmake_minimum_required(VERSION 3.29)
project(xxhash)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp
        src/xxhash/XXHash32.cpp
        src/xxhash/XXHash64.cpp
        src/Benchmark.cpp)

add_executable(gtest_xxhash
        src/xxhash/XXHash32.cpp
        src/xxhash/XXHash64.cpp
        src/test/XXHash32Test.cpp
        src/test/XXHash64Test.cpp)

target_link_libraries(gtest_xxhash gtest gtest_main)