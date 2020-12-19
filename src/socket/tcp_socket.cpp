#include <rtw/socket/tcp_socket.h>

#include <chrono>
#include <iostream>

#include <boost/bind.hpp>

namespace rtw {

tcp_socket::tcp_socket(std::function<void(const unsigned char*, std::size_t)> read_callback, unsigned short local_port_number, const std::string& local_ip_address)
: io_service_{  }
, thread_{  }
, local_ip_address_{ local_ip_address }
, local_port_number_{ local_port_number }
, socket_{ io_service_ }
, read_buff_{  }
, read_callback_{ read_callback }
, is_started_{ false }
, is_connected_{ false }
{
    
}

void tcp_socket::start_io_service()
{
    thread_ = std::thread([this]() -> void {
        io_service_.reset();
        io_service_.run();
    });
}

void tcp_socket::stop_io_service()
{
    io_service_.stop();
    if (thread_.joinable()) {
        thread_.join();
    }
}

void tcp_socket::read()
{
    boost::asio::async_read(socket_, read_buff_, boost::asio::transfer_at_least(1), boost::bind(&tcp_socket::on_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void tcp_socket::on_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error) {
        std::cout << "read failed: " << error.message() << std::endl;
        is_connected_ = false;
        restart();
    }
    else {
        if (read_callback_) {
            read_callback_(boost::asio::buffer_cast<const unsigned char*>(read_buff_.data()), bytes_transferred);
        }
        read_buff_.consume(read_buff_.size());
        read();
    }
}

void tcp_socket::on_write(const boost::system::error_code& error, std::size_t bytes_transferred, std::shared_ptr<std::vector<unsigned char>>)
{
    if (error.value() != 0) {
        std::cout << "failed to write. error code = " << error.value() << ", message: " << error.message() << std::endl;
    }
}

void tcp_socket::shutdown()
{
    // shutdown
    boost::system::error_code error;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
    if (error) {
        std::cout << "shutdown failed: " << error.message() << std::endl;
    }
}

void tcp_socket::close()
{
    // close
    boost::system::error_code error;
    socket_.close(error);
    if (error) {
        std::cout << "close failed: " << error.message() << std::endl;
    }

    // clear buffer
    read_buff_.consume(read_buff_.size());
}

bool tcp_socket::write(const std::vector<unsigned char>& data)
{
    if (!is_connected_) {
        return false;
    }
    std::shared_ptr<std::vector<unsigned char>> buffer = std::make_shared<std::vector<unsigned char>>(data);
    boost::asio::async_write(socket_, boost::asio::buffer(*buffer), boost::bind(&tcp_socket::on_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, buffer));
    return true;
}

bool tcp_socket::write(const unsigned char* data, std::size_t size)
{
    if (!is_connected_) {
        return false;
    }
    std::shared_ptr<std::vector<unsigned char>> buffer = std::make_shared<std::vector<unsigned char>>(data, data + size);
    boost::asio::async_write(socket_, boost::asio::buffer(*buffer), boost::bind(&tcp_socket::on_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, buffer));
    return true;
}

bool tcp_socket::stop()
{
    if (!is_started_) {
        return false;
    }
    stop_io_service();
    close();
    is_started_ = false;
    return true;
}

bool tcp_socket::is_started() const
{
    return is_started_;
}

bool tcp_socket::is_connected() const
{
    return is_connected_;
}

}