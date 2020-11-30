#include <rtw/socket/tcp_client.h>

#include <chrono>
#include <iostream>

#include <boost/bind.hpp>

namespace rtw {

tcp_client::tcp_client()
: io_service_{  }
, thread_{  }
, local_ip_address_{ "0.0.0.0" }
, local_port_number_{ 0 }
, remote_ip_address_{ "127.0.0.1" }
, remote_port_number_{ 0 }
, socket_{ io_service_ }
, read_buff_{  }
, read_callback_{  }
, is_started_{ false }
, is_connected_{ false }
{
    
}

void tcp_client::start_io_service()
{
    thread_ = std::thread([this]() -> void {
        io_service_.reset();
        io_service_.run();
    });
}

void tcp_client::stop_io_service()
{
    io_service_.stop();
    if (thread_.joinable()) {
        thread_.join();
    }
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

void tcp_client::read()
{
    boost::asio::async_read(socket_, read_buff_, boost::asio::transfer_at_least(1), boost::bind(&tcp_client::on_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void tcp_client::on_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error) {
        std::cout << "read failed: " << error.message() << std::endl;
        is_connected_ = false;
        close();
        open();
        connect();
    }
    else {
        if (read_callback_) {
            read_callback_(boost::asio::buffer_cast<const unsigned char*>(read_buff_.data()), bytes_transferred);
        }
        read_buff_.consume(read_buff_.size());
        read();
    }
}

void tcp_client::on_write(const boost::system::error_code& error, std::size_t bytes_transferred, std::shared_ptr<std::vector<unsigned char>>)
{
    if (error.value() != 0) {
        std::cout << "failed to write. error code = " << error.value() << ", message: " << error.message() << std::endl;
    }
}

void tcp_client::close()
{
    // shutdown
    boost::system::error_code error;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
    if (error) {
        std::cout << "shutdown failed: " << error.message() << std::endl;
    }

    // close
    socket_.close(error);
    if (error) {
        std::cout << "close failed: " << error.message() << std::endl;
    }

    // clear buffer
    read_buff_.consume(read_buff_.size());
}

bool tcp_client::start(std::function<void(const unsigned char*, std::size_t)> read_callback, const std::string& remote_ip_address, unsigned short remote_port_number, const std::string& local_ip_address, unsigned short local_port_number)
{
    if (is_started_) {
        return false;
    }
    is_started_ = true;
    read_callback_ = read_callback;
    local_ip_address_ = local_ip_address;
    local_port_number_ = local_port_number;
    remote_ip_address_ = remote_ip_address;
    remote_port_number_ = remote_port_number;
    open();
    connect();
    start_io_service();
    return true;
}

bool tcp_client::write(const std::vector<unsigned char>& data)
{
    if (!is_connected_) {
        return false;
    }
    std::shared_ptr<std::vector<unsigned char>> buffer = std::make_shared<std::vector<unsigned char>>(data);
    boost::asio::async_write(socket_, boost::asio::buffer(*buffer), boost::bind(&tcp_client::on_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, buffer));
    return true;
}

bool tcp_client::write(const unsigned char* data, std::size_t size)
{
    if (!is_connected_) {
        return false;
    }
    std::shared_ptr<std::vector<unsigned char>> buffer = std::make_shared<std::vector<unsigned char>>(data, data + size);
    boost::asio::async_write(socket_, boost::asio::buffer(*buffer), boost::bind(&tcp_client::on_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, buffer));
    return true;
}

bool tcp_client::stop()
{
    if (!is_started_) {
        return false;
    }
    is_started_ = false;
    stop_io_service();
    close();
    return true;
}

} // namespace rtw