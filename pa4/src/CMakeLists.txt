add_executable(
    pa4.out
    pa4.cpp
)

add_library(
    pa4.lib
    graph.cpp
    utils.cpp
)

target_link_libraries(
    pa4.out
    pa4.lib
)

add_executable(
    pa4.evaluate.out
    evaluate.cpp
)

target_compile_options(pa4.lib PRIVATE -Wno-macro-redefined)
target_compile_options(pa4.out PRIVATE -Wno-macro-redefined)
