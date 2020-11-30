#include <iostream>
#include "TcpUtil.h"
#include "Utils.h"

void TcpUtil::SendMsg(std::string message)
{
    std::cout << "Sending: " << message << std::endl;
    std::string modified_message = message + "\r\n\r\n";
    int bytes_sent = send(_socket, modified_message.c_str(), strlen(modified_message.c_str()), 0);
    if (bytes_sent == SOCKET_ERROR)
    {
        std::cout << "could not send message" << std::endl;
        std::cout << "error " << WSAGetLastError() << std::endl;
    }
}

std::string TcpUtil::ReceiveMsg()
{
    _buf[0] = 0;
    int bytes_received = 0;
    while (!Utils::StringEndsWith(std::string(_buf), "\r\n\r\n"))
    {
        bytes_received += recv(_socket, _buf + bytes_received, buffer_size - bytes_received - 1, 0);
        if (bytes_received == SOCKET_ERROR || bytes_received == 0)
        {
            return "";
        }
        _buf[bytes_received] = 0;
    }
    int processed = 0;
    std::string message = std::string(_buf);
    while (!message.empty())
    {
        size_t length = message.find("\r\n\r\n");
        processed = length + 4;
        std::string submessage = message.substr(0, length);
        if (_logging) std::cout << "Received: " << submessage << std::endl;
        _messages.push(submessage);

        message = message.substr(processed);
    }
    std::string result = _messages.front();
    _messages.pop();
    return result;
}

TcpUtil::~TcpUtil()
{
    closesocket(_socket);
    delete[] _buf;
}
