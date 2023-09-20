include_directories(${PA4_ROOT}/include)

add_subdirectory(
    src
    build
)

add_subdirectory(
    tests
    build/tests
)
