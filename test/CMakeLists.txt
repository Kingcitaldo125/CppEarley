cmake_minimum_required(VERSION 3.10)

project(CppEarleyTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)

set(PROJECT_ROOT_DIRECTORY "${CMAKE_SOURCE_DIR}/../")

message("PROJECT_ROOT_DIRECTORY: ${PROJECT_ROOT_DIRECTORY}")

find_library(CPP_EARLEY cpp_earley
    HINTS ${PROJECT_ROOT_DIRECTORY}
    PATH_SUFFIXES /lib /build/src)
    
add_executable(app-test test.cpp)

target_link_libraries(app-test ${CPP_EARLEY} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

target_include_directories(app-test PUBLIC ${PROJECT_ROOT_DIRECTORY}/include)

