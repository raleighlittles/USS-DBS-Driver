cmake_minimum_required(VERSION 3.30)

project(us_solid_precision_balance_driver 
DESCRIPTION "A driver for US Solid Precision Balance scales (USS-DBS28)" 
LANGUAGES "CXX"
HOMEPAGE_URL "https://github.com/raleighlittles/USS-DBS-Driver")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_executable(${PROJECT_NAME} main.cpp Measurement.hpp constants.h converter.h converter.cpp)