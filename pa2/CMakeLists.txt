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
set(CTEST_PARALLEL_LEVEL 4)

function(pa2_test test_name)
    if (ARGN)
        set(display_test_name "${test_name}::${ARGN}")
    else()
        set(display_test_name "${test_name}")
    endif()
    add_test(
        NAME PA2::${display_test_name}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/build/tests/pa2.test.out ${test_name} ${ARGN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endfunction(pa2_test)

pa2_test(Task1)
pa2_test(Task2)
pa2_test(Task3 PRE)
pa2_test(Task3 IN)
pa2_test(Task3 POST)
pa2_test(Task3 LEVEL)
pa2_test(Task4 PRE)
pa2_test(Task4 POST)
pa2_test(Task5)
pa2_test(Task6)
