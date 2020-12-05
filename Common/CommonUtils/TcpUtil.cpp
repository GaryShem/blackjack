#include <iostream>
#include "TcpUtil.h"
#include "Utils.h"

void TcpUtil::SendMsg(std::string message)
{
    if (_logging)
    {
        std::cout << "Sending: " << message << std::endl;
    }
    std::string modified_message = message + "\r\n\r\n";
    boost::asio::write(*_socket, boost::asio::buffer(modified_message, modified_message.length()));
}

std::string TcpUtil::ReceiveMsg()
{
    std::string data;
    int bytes_received = boost::asio::read_until(*_socket, boost::asio::dynamic_buffer(data), "\r\n\r\n");
    std::string message = data.substr(0, bytes_received - 4);
    if (_logging)
    {
        std::cout << "Receiving: " << message << std::endl;
    }
    return message;
}
