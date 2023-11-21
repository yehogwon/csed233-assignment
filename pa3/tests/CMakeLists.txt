include_directories(
    ${PA3_ROOT}/include
    ${PA3_ROOT}/src
    ${PA_ROOT}/tests
)

add_executable(
    pa3.test.out
    pa3.test.cpp
)

target_link_libraries(
    pa3.test.out
    pa3.lib
)
