cmake_minimum_required(VERSION 3.1.0)

project(AdatExamples)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../bin")

include_directories( "${PROJECT_SOURCE_DIR}/../include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3 -Wall -Wextra -Werror")

add_definitions(-DEXTEND_ADAT)

add_executable(example_fmt fmtlib.cpp)

add_executable(example_plog plog.cpp)

add_executable(example_json json.cpp)

add_executable(example_indicators indicators.cpp)

add_executable(example_tabulate tabulate.cpp)

add_executable(example_timers timers.cpp)

add_executable(example_slicer stl_container_slicer.cpp)

add_executable(example_string_methods python_string_methods.cpp)

add_executable(example_cxxopts cxxopts.cpp)

