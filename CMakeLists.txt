cmake_minimum_required(VERSION 3.10)

project(CppEarley VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

add_executable(cpp_earley src/main.cpp)

#target_link_libraries(cpp_earley PUBLIC cpp_earley)

target_include_directories(cpp_earley PUBLIC "include/")

