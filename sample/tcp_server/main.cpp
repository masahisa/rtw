#include <chrono>
#include <iostream>
#include <thread>

#include <rtw/socket/tcp_server.h>

void callback(const unsigned char* data, std::size_t size)
{
    
}

int main()
{
    rtw::tcp_server server;
    server.start(callback, 50001, "127.0.0.1");

    std::vector<unsigned char> data{ 0x6B, 0x6F, 0x6E, 0x6E, 0x6F };
    unsigned char array[] = { 0x4B, 0x4F, 0x4E, 0x4E, 0x4F };

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        server.write(data);
        server.write(array, sizeof(array));
    }

    return 0;
}
