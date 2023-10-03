add_executable(
    pa2.out
    pa2.cpp
)

add_library(
    pa2.lib
    utils.cpp
    heap.cpp
    tree.cpp
)

target_link_libraries(
    pa2.out
    pa2.lib
)

add_executable(
    pa2.evaluate.out
    evaluate.cpp
)
