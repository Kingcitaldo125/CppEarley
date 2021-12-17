set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

enable_testing()

find_package(GTest REQUIRED)

set(TEST_GRAMMAR_DIRECTORY "${CMAKE_SOURCE_DIR}/test/test_grammars/")

set(CPP_EARLEY cpp_earley)

add_executable(app-test test.cpp)

target_link_libraries(app-test ${CPP_EARLEY} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

target_include_directories(app-test PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

add_test(NAME app-test-test COMMAND app-test ${TEST_GRAMMAR_DIRECTORY})
