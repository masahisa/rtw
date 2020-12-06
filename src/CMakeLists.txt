cmake_minimum_required(VERSION 2.8)

# add library
add_library(
    ${PROJECT_NAME}
    SHARED
    "socket/tcp_client.cpp"
    "socket/tcp_server.cpp"
    "socket/udp_socket.cpp"
)