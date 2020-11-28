#include <chrono>
#include <iostream>
#include <thread>

#include <rtw/socket/tcp_server.h>

int main()
{
    rtw::tcp_server server;
    server.start(50001, "127.0.0.1");

    std::vector<unsigned char> data{ 0x6B, 0x6F, 0x6E, 0x6E, 0x6F };

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        server.write(data);
    }

    return 0;
}
