add_executable(
    pa3.out
    pa3.cpp
)

add_library(
    pa3.lib
    utils.cpp
    closed_hash_function.cpp
    closed_hash_table.cpp
    open_hash_function.cpp
    open_hash_table.cpp
    sort.cpp
    tree.cpp
    bst.cpp
    avl.cpp
)

target_link_libraries(
    pa3.out
    pa3.lib
)

add_executable(
    pa3.evaluate.out
    evaluate.cpp
)
