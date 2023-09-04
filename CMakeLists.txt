if (POLICY CMP0025)
cmake_policy(SET CMP0025 NEW)
endif()

project("CSED233 Programming Assignment")
cmake_minimum_required(VERSION 3.10)

# set (CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(pa1)
add_subdirectory(pa2)
add_subdirectory(pa3)
add_subdirectory(pa4)
