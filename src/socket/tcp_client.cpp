#include <rtw/socket/tcp_client.h>

#include <iostream>

#include <boost/bind.hpp>

namespace rtw {

tcp_client::tcp_client(std::function<void(const unsigned char*, std::size_t)> read_callback, const std::string& remote_ip_address, unsigned short remote_port_number, const std::string& local_ip_address, unsigned short local_port_number)
: tcp_socket{ read_callback, local_port_number, local_ip_address }
, remote_ip_address_{ remote_ip_address }
, remote_port_number_{ remote_port_number }
{

}

void tcp_client::open()
{
    // open a socket
    boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v4();
    boost::system::error_code error_code;
    socket_.open(protocol, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to open a socket. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }

    // set sock opt
    socket_.set_option(boost::asio::socket_base::reuse_address(true), error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to set a socket option. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }

    // set sock option (no_delay)
    socket_.set_option(boost::asio::ip::tcp::no_delay(true), error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to set a socket option (no_delay). error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }

    // create a local endpoint
    boost::asio::ip::address address = boost::asio::ip::address::from_string(local_ip_address_, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to parse the ip address. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }
    boost::asio::ip::tcp::endpoint endpoint{ address, local_port_number_ };

    // bind a socket to a local endpoint
    socket_.bind(endpoint, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to bind a socket. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }
}

void tcp_client::connect()
{
    // create a remote endpoint
    boost::system::error_code error_code;
    boost::asio::ip::address address = boost::asio::ip::address::from_string(remote_ip_address_, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to parse the ip address. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }
    boost::asio::ip::tcp::endpoint endpoint{ address, remote_port_number_ };

    // connect to a remote endpoint
    socket_.async_connect(endpoint, boost::bind(&tcp_client::on_connect, this, boost::asio::placeholders::error));
}

void tcp_client::on_connect(const boost::system::error_code& error)
{
    if (error) {
        std::cout << "connect failed: " << error.message() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        connect();
    }
    else {
        is_connected_ = true;
        read();
    }
}

void tcp_client::restart()
{
    close();
    open();
    connect();
}

bool tcp_client::start()
{
    if (is_started_) {
        return false;
    }
    is_started_ = true;
    open();
    connect();
    start_io_service();
    return true;
}

} // namespace rtw