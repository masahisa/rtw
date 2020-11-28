cmake_minimum_required(VERSION 2.8)

# project name
project(rtw)

# cmake option
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")

# output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# include directories
include_directories(include)

# add subdirectories
add_subdirectory(src)

# add test subdirectories
add_subdirectory(test)

# add sample subdirectories
add_subdirectory(sample)

# test
enable_testing()
add_test(
    NAME all_tests
    COMMAND $<TARGET_FILE:run_all_tests>
)

# add doc subdirectories
add_subdirectory(doc)

# add cov subdirectories
add_subdirectory(cov)