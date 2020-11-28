cmake_minimum_required(VERSION 2.8)

# add executable
add_executable(
    tcp_server
    "main.cpp"
)

# target link libraries
target_link_libraries(
    tcp_server
    boost_system
    pthread
    rtw
)