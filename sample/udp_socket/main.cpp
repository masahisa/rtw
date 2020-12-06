#include <chrono>
#include <iostream>
#include <thread>

#include <rtw/socket/udp_socket.h>

void callback1(const unsigned char* data, std::size_t size)
{
    std::cout << "callback1 called: " << size << std::endl;
}

void callback2(const unsigned char* data, std::size_t size)
{
    std::cout << "callback2 called: " << size << std::endl;
}

int main()
{
    rtw::udp_socket socket1;
    socket1.start(callback1, "127.0.0.1", 50001, "0.0.0.0", 60001);

    rtw::udp_socket socket2;
    socket2.start(callback2, "127.0.0.1", 60001, "0.0.0.0", 50001);

    std::vector<unsigned char> data1{ 0x6B, 0x6F, 0x6E, 0x6E, 0x6F };
    unsigned char array1[] = { 0x4B, 0x4F, 0x4E, 0x4E, 0x4F };

    std::vector<unsigned char> data2{ 0x6D, 0x61, 0x73, 0x61, 0x68, 0x69, 0x73, 0x61 };
    unsigned char array2[] = { 0x4D, 0x41, 0x53, 0x41, 0x48, 0x49, 0x53, 0x41 };

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        socket1.send(data1);
        socket1.send(array1, sizeof(array1));

        socket2.send(data2);
        socket2.send(array2, sizeof(array2));
    }

    return 0;
}
