#ifndef BLACKJACK_TCPUTIL_H
#define BLACKJACK_TCPUTIL_H

#include <string>
#include <queue>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpUtil
{
public:
    const int buffer_size = 1024*1024;

    void SendMsg(std::string message);
    std::string ReceiveMsg();
    bool _logging = true;
protected:
    std::shared_ptr<boost::asio::io_context> _context;
    std::queue<std::string> _messages;
    std::shared_ptr<tcp::socket> _socket;
};


#endif //BLACKJACK_TCPUTIL_H
