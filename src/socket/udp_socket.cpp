#include <rtw/socket/udp_socket.h>

#include <chrono>
#include <iostream>

#include <boost/bind.hpp>

namespace rtw {

udp_socket::udp_socket()
: io_service_{  }
, thread_{  }
, local_ip_address_{ "0.0.0.0" }
, local_port_number_{ 0 }
, remote_ip_address_{ "127.0.0.1" }
, remote_port_number_{ 0 }
, socket_{ io_service_ }
, receive_buff_{  }
, receive_callback_{  }
, is_started_{ false }
{

}

void udp_socket::start_io_service()
{
    thread_ = std::thread([this]() -> void {
        io_service_.reset();
        io_service_.run();
    });
}

void udp_socket::stop_io_service()
{
    io_service_.stop();
    if (thread_.joinable()) {
        thread_.join();
    }
}

void udp_socket::open()
{
    // open socket
    boost::asio::ip::udp protocol = boost::asio::ip::udp::v4();
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

    // create a local endpoint
    boost::asio::ip::address address = boost::asio::ip::address::from_string(local_ip_address_, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to parse the ip address. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }
    boost::asio::ip::udp::endpoint endpoint{ address, local_port_number_ };

    // bind a socket to a local endpoint
    socket_.bind(endpoint, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to bind a socket. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }
}

void udp_socket::receive()
{
    // create a remote endpoint
    boost::system::error_code error_code;
    boost::asio::ip::address address = boost::asio::ip::address::from_string(remote_ip_address_, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to parse the ip address. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
    }
    // async read from
    boost::asio::ip::udp::endpoint endpoint{ address, remote_port_number_ };
    socket_.async_receive_from(receive_buff_.prepare(65536), endpoint, boost::bind(&udp_socket::on_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void udp_socket::on_receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error) {
        std::cout << "receive failed: " << error.message() << std::endl;
        close();
        open();
        receive();
    }
    else {
        if (receive_callback_) {
            receive_callback_(boost::asio::buffer_cast<const unsigned char*>(receive_buff_.data()), bytes_transferred);
        }
        receive_buff_.consume(receive_buff_.size());
        receive();
    }
}

void udp_socket::on_send(const boost::system::error_code& error, std::size_t bytes_transferred, std::shared_ptr<std::vector<unsigned char>>)
{
    if (error.value() != 0) {
        std::cout << "failed to send. error code = " << error.value() << ", message: " << error.message() << std::endl;
    }
}

void udp_socket::close()
{
    // shutdown
    boost::system::error_code error;
    socket_.shutdown(boost::asio::ip::udp::socket::shutdown_both, error);
    if (error) {
        std::cout << "shutdown failed: " << error.message() << std::endl;
    }

    // close
    socket_.close(error);
    if (error) {
        std::cout << "close failed: " << error.message() << std::endl;
    }

    // clear buffer
    receive_buff_.consume(receive_buff_.size());
}

bool udp_socket::start(std::function<void(const unsigned char*, std::size_t)> receive_callback, const std::string& remote_ip_address, unsigned short remote_port_number, const std::string& local_ip_address, unsigned short local_port_number)
{
    if (is_started_) {
        return false;
    }
    is_started_ = true;
    receive_callback_ = receive_callback;
    remote_ip_address_ = remote_ip_address;
    remote_port_number_ = remote_port_number;
    local_ip_address_ = local_ip_address;
    local_port_number_ = local_port_number;
    open();
    receive();
    start_io_service();
    return true;
}

bool udp_socket::send(const std::vector<unsigned char>& data)
{
    if (!is_started_) {
        return false;
    }
    // create a remote endpoint
    boost::system::error_code error_code;
    boost::asio::ip::address address = boost::asio::ip::address::from_string(remote_ip_address_, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to parse the ip address. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
        return false;
    }
    boost::asio::ip::udp::endpoint endpoint{ address, remote_port_number_ };
    // async send to
    std::shared_ptr<std::vector<unsigned char>> buffer = std::make_shared<std::vector<unsigned char>>(data);
    socket_.async_send_to(boost::asio::buffer(*buffer), endpoint, boost::bind(&udp_socket::on_send, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, buffer));
    return true;
}

bool udp_socket::send(const unsigned char* data, std::size_t size)
{
    if (!is_started_) {
        return false;
    }
    // create a remote endpoint
    boost::system::error_code error_code;
    boost::asio::ip::address address = boost::asio::ip::address::from_string(remote_ip_address_, error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to parse the ip address. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
        return false;
    }
    boost::asio::ip::udp::endpoint endpoint{ address, remote_port_number_ };
    // async send to
    std::shared_ptr<std::vector<unsigned char>> buffer = std::make_shared<std::vector<unsigned char>>(data, data + size);
    socket_.async_send_to(boost::asio::buffer(*buffer), endpoint, boost::bind(&udp_socket::on_send, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, buffer));
    return true;
}

bool udp_socket::stop()
{
    if (!is_started_) {
        return false;
    }
    is_started_ = false;
    stop_io_service();
    close();
    return true;
}

bool udp_socket::is_started() const
{
    return is_started_;
}

} // namespace rtw