#ifndef RTW_TCP_SERVER_H
#define RTW_TCP_SERVER_H

#include <rtw/socket/tcp_socket.h>

namespace rtw {

class tcp_client : public tcp_socket {
private:
    std::string remote_ip_address_;
    unsigned short remote_port_number_;
public:
    tcp_client(std::function<void(const unsigned char*, std::size_t)> read_callback, const std::string& remote_ip_address, unsigned short remote_port_number, const std::string& local_ip_address = "0.0.0.0", unsigned short local_port_number = 0);
private:
    void open() override;
    void connect();
    void on_connect(const boost::system::error_code& error);
    void restart() override;
public:
    bool start();
};

} // namespace rtw

#endif // RTW_TCP_SERVER_H