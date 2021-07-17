cmake_minimum_required(VERSION 3.10)

project(CppEarley VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

set(PROJECT_DIRECTORY "${CMAKE_SOURCE_DIR}")

option(COPY_LIBS "Copy the static/shared libs to a 'lib' folder in the 'CMAKE_SOURCE_DIR'" ON)

if(COPY_LIBS)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

include_directories(include)

add_subdirectory(include)
add_subdirectory(src)

add_executable(main src/main.cpp)

target_link_libraries(main PUBLIC cpp_earley)

target_include_directories(main PUBLIC "include/")

