#ifndef RTW_UDP_SOCKET_H
#define RTW_UDP_SOCKET_H

#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio.hpp>

namespace rtw {

class udp_socket {
private:
    boost::asio::io_service io_service_;
    std::thread thread_;
    std::string local_ip_address_;
    unsigned short local_port_number_;
    std::string remote_ip_address_;
    unsigned short remote_port_number_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::streambuf receive_buff_;
    std::function<void(const unsigned char*, std::size_t)> receive_callback_;
    bool is_started_;
public:
    udp_socket();
private:
    void start_io_service();
    void stop_io_service();
    void open();
    void receive();
    void on_receive(const boost::system::error_code& error, std::size_t bytes_transferred);
    void on_send(const boost::system::error_code& error, std::size_t bytes_transferred, std::shared_ptr<std::vector<unsigned char>>);
    void close();
public:
    bool start(std::function<void(const unsigned char*, std::size_t)> receive_callback, const std::string& remote_ip_address, unsigned short remote_port_number, const std::string& local_ip_address = "0.0.0.0", unsigned short local_port_number = 0);
    bool send(const std::vector<unsigned char>& data);
    bool send(const unsigned char* data, std::size_t size);
    bool stop();
    bool is_started() const;
};

} // namespace rtw

#endif // RTW_UDP_SOCKET_H