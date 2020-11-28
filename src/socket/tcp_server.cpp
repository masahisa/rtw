#include <rtw/socket/tcp_server.h>

#include <iostream>

#include <boost/bind.hpp>

namespace rtw {

tcp_server::tcp_server()
: io_service_{  }
, thread_{  }
, local_ip_address_{ "0.0.0.0" }
, local_port_number_{ 0 }
, acceptor_{ io_service_ }
, socket_{ io_service_ }
, read_buff_{  }
, is_started_{ false }
, is_connected_{ false }
{
    
}

void tcp_server::start_io_service()
{
    thread_ = std::thread([this]() -> void {
        io_service_.reset();
        io_service_.run();
    });
}

void tcp_server::stop_io_service()
{
    io_service_.stop();
    if (thread_.joinable()) {
        thread_.join();
    }
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

    // set sock option
    acceptor_.set_option(boost::asio::socket_base::reuse_address(true), error_code);
    if (error_code.value() != 0) {
        std::cout << "failed to set a socket option. error code = " << error_code.value() << ", message: " << error_code.message() << std::endl;
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

void tcp_server::read()
{
    boost::asio::async_read(socket_, read_buff_, boost::asio::transfer_at_least(1), boost::bind(&tcp_server::on_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void tcp_server::on_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error) {
        std::cout << "read failed: " << error.message() << std::endl;
        is_connected_ = false;
        close();
        accept();
    }
    else {
        read_buff_.consume(read_buff_.size());
        read();
    }
}

void tcp_server::on_write(const boost::system::error_code& error, std::size_t bytes_transferred, std::shared_ptr<std::vector<unsigned char>>)
{
    if (error.value() != 0) {
        std::cout << "failed to write. error code = " << error.value() << ", message: " << error.message() << std::endl;
    }
}

void tcp_server::close()
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
}

bool tcp_server::start(unsigned short local_port_number, const std::string& local_ip_address)
{
    if (is_started_) {
        return false;
    }
    is_started_ = true;
    local_port_number_ = local_port_number;
    local_ip_address_ = local_ip_address;
    open();
    accept();
    start_io_service();
    return true;
}

bool tcp_server::write(const std::vector<unsigned char>& data)
{
    if (!is_connected_){
        return false;
    }
    std::shared_ptr<std::vector<unsigned char>> buffer = std::make_shared<std::vector<unsigned char>>(data);
    boost::asio::async_write(socket_, boost::asio::buffer(*buffer), boost::bind(&tcp_server::on_write, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, buffer));
    return true;
}

bool tcp_server::stop()
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