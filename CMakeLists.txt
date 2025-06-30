# Minimum version of CMake
cmake_minimum_required(VERSION 3.12)

# Project name and language
project(bridges LANGUAGES CXX)

# Set the C++ standard (C++17 or C++20)
set(CMAKE_CXX_STANDARD 20)  # Change to 17 if using C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_BUILD_TYPE Release)

set(SOURCES
    main.cpp
    )
# Add the executable
add_executable(bridges ${SOURCES})

# Specify the compiler for each platform
if(WIN32)
  set(CMAKE_CXX_COMPILER C:/Program\ Files/LLVM/bin/clang++.exe)
elseif(UNIX)
  set(CMAKE_CXX_COMPILER /usr/bin/g++)
endif()