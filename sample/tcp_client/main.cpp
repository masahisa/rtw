#include <chrono>
#include <iostream>
#include <thread>

#include <rtw/socket/tcp_client.h>

void callback(const unsigned char* data, std::size_t size)
{
    
}

int main()
{
    rtw::tcp_client client(callback, "127.0.0.1", 50001, "127.0.0.1", 60001);
    client.start();

    std::vector<unsigned char> data{ 0x6D, 0x61, 0x73, 0x61, 0x68, 0x69, 0x73, 0x61 };
    unsigned char array[] = { 0x4D, 0x41, 0x53, 0x41, 0x48, 0x49, 0x53, 0x41 };

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        client.write(data);
        client.write(array, sizeof(array));
    }

    return 0;
}
