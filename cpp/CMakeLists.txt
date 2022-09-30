cmake_minimum_required(VERSION 3.22)
project(us_solid_precision_balance_driver DESCRIPTION "A driver for US Solid Precision Balance scales (USS-DBS28)" LANGUAGES "CXX")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g  -D_DEBUG -D_GLIBCXX_DEBUG")

add_executable(${PROJECT_NAME} main.cpp Measurement.hpp constants.h converter.h converter.cpp)