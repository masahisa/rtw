#include <rtw/socket/tcp_server.h>

#include <iostream>

#include <boost/bind.hpp>

namespace rtw {

tcp_server::tcp_server(std::function<void(const unsigned char*, std::size_t)> read_callback, unsigned short local_port_number, const std::string& local_ip_address)
: tcp_socket{ read_callback, local_port_number, local_ip_address }
, acceptor_{ io_service_ }
{

}

void tcp_server::open()
{
    // open an acceptor
    boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v4();
    boost::system::error_code error_code;
    acceptor_.open(protocol, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to open an acceptor. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }

    // set sock option (reuse_address)
    acceptor_.set_option(boost::asio::socket_base::reuse_address(true), error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to set a socket option (reuse_address). error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }

    // set sock option (no_delay)
    acceptor_.set_option(boost::asio::ip::tcp::no_delay(true), error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to set a socket option (no_delay). error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }

    // create a local endpoint to listen
    boost::asio::ip::address address = boost::asio::ip::address::from_string(local_ip_address_, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to parse the ip address. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }
    boost::asio::ip::tcp::endpoint endpoint{ address, local_port_number_ };

    // bind to a local endpoint
    acceptor_.bind(endpoint, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to bind an acceptor. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }

    // listen
    acceptor_.listen();
}

void tcp_server::accept()
{
    acceptor_.async_accept(socket_, boost::bind(&tcp_server::on_accept, this, boost::asio::placeholders::error));
}

void tcp_server::on_accept(const boost::system::error_code& error)
{
    if (error) {
        std::cout << "accept failed: " << error.message() << std::endl;
        accept();
    }
    else {
        is_connected_ = true;
        read();
    }
}

void tcp_server::restart()
{
    close();
    accept();
}

bool tcp_server::start()
{
    if (is_started_) {
        return false;
    }
    is_started_ = true;
    open();
    accept();
    start_io_service();
    return true;
}

} // namespace rtw