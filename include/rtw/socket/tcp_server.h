#ifndef RTW_TCP_SERVER_H
#define RTW_TCP_SERVER_H

#include <rtw/socket/tcp_socket.h>

namespace rtw {

class tcp_server : public tcp_socket {
private:
    boost::asio::ip::tcp::acceptor acceptor_;
public:
    tcp_server(std::function<void(const unsigned char*, std::size_t)> read_callback, unsigned short local_port_number, const std::string& local_ip_address = "0.0.0.0");
private:
    void open() override;
    void accept();
    void on_accept(const boost::system::error_code& error);
    void restart() override;
public:
    bool start() override;
};

} // namespace rtw

#endif // RTW_TCP_SERVER_H