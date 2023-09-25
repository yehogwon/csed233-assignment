include_directories(${PA1_ROOT}/include)

add_subdirectory(
    src
    build
)

add_subdirectory(
    tests
    build/tests
)

include(CTest)

function(pa1_test test_name)
    add_test(
        NAME PA1::${test_name}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/build/tests/pa1.test.out ${test_name}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endfunction(pa1_test)

pa1_test(Task1)
pa1_test(Task2)
pa1_test(Task3)
pa1_test(Task4)
pa1_test(Task5)
# pa1_test(Task6)
