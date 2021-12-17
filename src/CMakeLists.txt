
add_library(cpp_earley STATIC grammar.cpp earley.cpp)
add_library(cpp_earley_shared SHARED grammar.cpp earley.cpp)

add_executable(${MAIN_TARGET} main.cpp)
target_link_libraries(${MAIN_TARGET} PRIVATE cpp_earley)
