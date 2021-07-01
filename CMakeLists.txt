cmake_minimum_required(VERSION 3.10)

project(CppEarley VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_DIRECTORY "${CMAKE_SOURCE_DIR}")

message("PROJECT_DIR: ${PROJECT_DIRECTORY}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_DIRECTORY}/lib)

include_directories(include)

add_subdirectory(src)

add_executable(main src/main.cpp)

target_link_libraries(main PUBLIC cpp_earley)

target_include_directories(main PUBLIC "include/")

