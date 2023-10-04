include_directories(
    ${PA2_ROOT}/include
    ${PA2_ROOT}/src
    ${PA_ROOT}/tests
)

add_executable(
    pa2.test.out
    pa2.test.cpp
)

target_link_libraries(
    pa2.test.out
    pa2.lib
)
