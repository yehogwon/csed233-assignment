include_directories(
    ${PA4_ROOT}/include
    ${PA4_ROOT}/src
    ${PA_ROOT}/tests
)

add_executable(
    pa4.test.out
    pa4.test.cpp
)

target_link_libraries(
    pa4.test.out
    pa4.lib
)

target_compile_options(pa4.test.out PRIVATE -Wno-macro-redefined)
