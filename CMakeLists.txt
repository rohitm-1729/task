cmake_minimum_required(VERSION 3.12.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")
project(RAW2PGM)

include_directories(header)
file (GLOB SOURCES "src/*.cpp")
add_executable(convert ${SOURCES})