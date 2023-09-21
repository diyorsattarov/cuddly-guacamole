cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME cpp-cmake-template)

project(${PROJECT_NAME})

add_subdirectory(src)

include_directories(include)

find_package(GTest REQUIRED)

add_custom_target(run_tests COMMAND tests)