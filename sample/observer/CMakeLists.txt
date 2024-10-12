cmake_minimum_required(VERSION 3.5)

# add executable
add_executable(
    observer
    "main.cpp"
)

# target link libraries
target_link_libraries(
    observer
    rtw
    pthread
)