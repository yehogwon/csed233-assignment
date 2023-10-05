include_directories(
    ${PA1_ROOT}/include
    ${PA1_ROOT}/src
    ${PA_ROOT}/tests
)

add_executable(
    pa1.test.out
    pa1.test.cpp
)

target_link_libraries(
    pa1.test.out
    pa1.lib
)

target_compile_features(pa1.test.out PRIVATE cxx_std_17)
