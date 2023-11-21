include_directories(${PA3_ROOT}/include)

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

function(pa3_test test_name)
    set(display_test_name "${test_name}")
    add_test(
        NAME PA3::${display_test_name}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/build/tests/pa3.test.out ${test_name}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endfunction(pa3_test)

pa3_test(Task1)
# pa3_test(Task2)
# pa3_test(Task3)
# pa3_test(Task4)
# pa3_test(Task5)
# pa3_test(Task6)
