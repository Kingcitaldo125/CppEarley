cmake_minimum_required(VERSION 3.10)

project(CppEarleyTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)

#[[

# Possible override for current test solution - requires hitting the internet each time ?

include(FetchContent)

FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
]]

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(app-test main.cpp)

#target_link_libraries(app-test gtest_main)
target_link_libraries(app-test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

add_test(NAME example_test COMMAND app-test)

