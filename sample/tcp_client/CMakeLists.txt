cmake_minimum_required(VERSION 2.8)

# add executable
add_executable(
    tcp_client
    "main.cpp"
)

# target link libraries
target_link_libraries(
    tcp_client
    boost_system
    pthread
    rtw
)