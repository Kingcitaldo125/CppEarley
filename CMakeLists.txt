cmake_minimum_required(VERSION 3.10)

project(CppEarley
  VERSION 1.3.1
  DESCRIPTION "Basic C++ Earley Parser"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(MAIN_TARGET main)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

option(BUILD_TESTS "Option to build the test suite" ON)

include_directories(include)

add_subdirectory(include)
add_subdirectory(src)

target_include_directories(${MAIN_TARGET}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/CppEarleyConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CppEarley
)

write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(TARGETS 
        cpp_earley
        cpp_earley_shared
        EXPORT CppEarleyTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT CppEarleyTargets
        FILE CppEarleyTargets.cmake
        NAMESPACE CppEarley::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CppEarley
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/CppEarleyConfig.cmake
        DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/CppEarley)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING
  PATTERN *.h
)

if(BUILD_TESTS)
  add_subdirectory(test)
  include(CTest)
endif()

# Must be last
include(CPack)
