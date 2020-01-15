cmake_minimum_required(VERSION 2.8)

# LD_LIBRARY_PATH
set(GTEST_LDFLAGS gtest gtest_main pthread)

# add executables
add_executable(
    run_all_tests
    "run_all_tests.cpp"
    "test_binary_search.cpp"
    "test_linear_search.cpp"
)

# target link libraries
target_link_libraries(
    run_all_tests
    ${GTEST_LDFLAGS}
)