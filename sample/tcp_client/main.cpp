#include <chrono>
#include <iostream>
#include <thread>

#include <rtw/socket/tcp_client.h>

int main()
{
    rtw::tcp_client client;
    client.start("127.0.0.1", 50001, "127.0.0.1", 60001);

    std::vector<unsigned char> data{ 0x6D, 0x61, 0x73, 0x61, 0x68, 0x69, 0x73, 0x61 };

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        client.write(data);
    }

    return 0;
}
