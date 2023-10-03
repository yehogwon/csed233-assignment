add_executable(
    pa1.out
    pa1.cpp
)

add_library(
    pa1.lib
    utils.cpp
)

target_link_libraries(
    pa1.out
    pa1.lib
)

add_executable(
    pa1.evaluate.out
    evaluate.cpp
)
