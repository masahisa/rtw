cmake_minimum_required(VERSION 2.8)

# add executable
add_executable(
    udp_socket
    "main.cpp"
)

# target link libraries
target_link_libraries(
    udp_socket
    boost_system
    pthread
    rtw
)