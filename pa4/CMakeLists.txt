include_directories(${PA4_ROOT}/include)

add_subdirectory(
    src
    build
)

add_subdirectory(
    tests
    build/tests
)

include(CTest)
set(CTEST_PARALLEL_LEVEL 4)

function(pa4_test test_name)
    set(display_test_name "${test_name}")
    add_test(
        NAME PA4::${display_test_name}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/build/tests/pa4.test.out ${test_name}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endfunction(pa4_test)

pa4_test(Task1)
pa4_test(Task2)
# pa4_test(Task3)
pa4_test(Task4)
pa4_test(Task5)
pa4_test(Task6)
pa4_test(Task7)
