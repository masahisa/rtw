#ifndef RTW_TCP_SERVER_H
#define RTW_TCP_SERVER_H

#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio.hpp>

namespace rtw {

class tcp_client {
private:
    boost::asio::io_service io_service_;
    std::thread thread_;
    std::string local_ip_address_;
    unsigned short local_port_number_;
    std::string remote_ip_address_;
    unsigned short remote_port_number_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf read_buff_;
    bool is_started_;
    bool is_connected_;
public:
    tcp_client();
private:
	void start_io_service();
	void stop_io_service();
    void open();
    void connect();
    void on_connect(const boost::system::error_code& error);
    void read();
    void on_read(const boost::system::error_code& error, std::size_t bytes_transferred);
    void on_write(const boost::system::error_code& error, std::size_t bytes_transferred, std::shared_ptr<std::vector<unsigned char>>);
    void close();
public:
    bool start(const std::string& remote_ip_address, unsigned short remote_port_number, const std::string& local_ip_address = "0.0.0.0", unsigned short local_port_number = 0);
    bool write(const std::vector<unsigned char>& data);
    bool stop();
};

} // namespace rtw

#endif // RTW_TCP_SERVER_H