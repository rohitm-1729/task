cmake_minimum_required(VERSION 3.12.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")
project(RAW2PGM)

include_directories(header)
file (GLOB SOURCES "src/*.cpp")

add_library(Image SHARED header/Image.hpp)

set_target_properties(Image PROPERTIES LINKER_LANGUAGE CXX)
add_executable(convert ${SOURCES})
target_link_libraries(convert PRIVATE Image)