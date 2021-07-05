cmake_minimum_required(VERSION 3.10)

project(CppEarleyTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

enable_testing()

find_package(GTest REQUIRED)

set(GRAMMAR_DIRECTORY "test_grammars")

set(PROJECT_ROOT_DIRECTORY "${CMAKE_SOURCE_DIR}/../")
set(TEST_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(TEST_GRAMMAR_DIRECTORY "${TEST_DIRECTORY}/${GRAMMAR_DIRECTORY}/")

message("PROJECT_ROOT_DIRECTORY: ${PROJECT_ROOT_DIRECTORY}")
message("TEST_DIRECTORY: ${TEST_DIRECTORY}")
message("TEST_GRAMMAR_DIRECTORY: ${TEST_GRAMMAR_DIRECTORY}")

find_library(CPP_EARLEY cpp_earley
    HINTS ${PROJECT_ROOT_DIRECTORY}
    PATH_SUFFIXES /lib /build/src)
    
add_executable(app-test test.cpp)

target_link_libraries(app-test ${CPP_EARLEY} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

target_include_directories(app-test PUBLIC ${PROJECT_ROOT_DIRECTORY}/include ${PROJECT_ROOT_DIRECTORY}/src)

add_test(NAME app-test-test COMMAND app-test ${TEST_GRAMMAR_DIRECTORY})

