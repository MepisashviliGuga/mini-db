cmake_minimum_required(VERSION 3.10)

# Project Name
project(MiniDB VERSION 1.0)

# Standard C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Where to look for header files (.h)
include_directories(include)

# Gather all source files
file(GLOB SOURCES "src/*.cpp")

# Create the executable named "minidb" from the source files
add_executable(minidb ${SOURCES})