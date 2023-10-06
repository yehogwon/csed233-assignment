include_directories(${PA2_ROOT}/include)

add_subdirectory(
    src
    build
)

add_subdirectory(
    tests
    build/tests
)

include(CTest)

function(pa2_test test_name)
    add_test(
        NAME PA2::${test_name}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/build/tests/pa2.test.out ${test_name}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endfunction(pa2_test)

pa2_test(Task1)
pa2_test(Task2)
pa2_test(Task3)
# pa2_test(Task4)
pa2_test(Task5)
# pa2_test(Task6)
