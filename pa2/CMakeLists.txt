include_directories(${PA2_ROOT}/include)

add_subdirectory(
    src
    build
)

add_subdirectory(
    tests
    build/tests
)
