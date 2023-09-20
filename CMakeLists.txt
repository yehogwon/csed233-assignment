if (POLICY CMP0025)
cmake_policy(SET CMP0025 NEW)
endif()

project("CSED233 Programming Assignment")
cmake_minimum_required(VERSION 3.10)

# set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

function(add_pa pa_name)
    string(TOUPPER ${pa_name} pa_name_upper)
    set(${pa_name_upper}_ROOT ${PROJECT_SOURCE_DIR}/${pa_name} CACHE INTERNAL "paroots")
    add_subdirectory(${pa_name})
endfunction(add_pa)

add_pa(pa1)
add_pa(pa2)
add_pa(pa3)
add_pa(pa4)
