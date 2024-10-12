cmake_minimum_required(VERSION 3.5)

# add library
add_library(
    ${PROJECT_NAME}
    SHARED
    "dp/observable.cpp"
    "socket/tcp_client.cpp"
    "socket/tcp_server.cpp"
    "socket/tcp_socket.cpp"
    "socket/udp_socket.cpp"
)