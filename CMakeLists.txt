cmake_minimum_required(VERSION 3.10)

project(CppEarley
  VERSION 1.1.0
  DESCRIPTION "Basic C++ Earley Parser"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(MAIN_TARGET main)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(include)

add_subdirectory(include)
add_subdirectory(src)

add_executable(${MAIN_TARGET} src/main.cpp)

target_link_libraries(${MAIN_TARGET} PUBLIC cpp_earley)

target_include_directories(${MAIN_TARGET}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS cpp_earley cpp_earley_shared DESTINATION ${CMAKE_INSTALL_LIBDIR})
