cmake_minimum_required(VERSION 3.10)

project(lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(lab4 main.cpp)

find_package(GTest REQUIRED)

add_executable(tests_lab4 tests/tests.cpp)
target_link_libraries(tests_lab4 GTest::gtest GTest::gtest_main)

enable_testing()
add_test(NAME lab4_tests COMMAND tests_lab4)