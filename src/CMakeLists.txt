cmake_minimum_required(VERSION 2.8)

# add library

# add executable
add_executable(
    ${PROJECT_NAME}
    "main.cpp"
    "measure_sorting_algorithms.cpp"
)

# target link libraries
target_link_libraries(
    ${PROJECT_NAME}
)
