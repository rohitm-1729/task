cmake_minimum_required(VERSION 3.12.2)
project(RAW2PGM)

include_directories(header)
file (GLOB SOURCES "src/*.cpp")
add_executable(convert ${SOURCES})