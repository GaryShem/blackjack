#ifndef BLACKJACK_TCPUTIL_H
#define BLACKJACK_TCPUTIL_H

#include <string>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <queue>

#pragma comment(lib, "Ws2_32.lib")

class TcpUtil
{
public:
    const int buffer_size = 1024*1024;

    void SendMsg(std::string message);
    std::string ReceiveMsg();
    bool _logging = true;

    virtual ~TcpUtil();
protected:
    std::queue<std::string> _messages;
    SOCKET _socket;

private:
    char* _buf = new char[buffer_size];
};


#endif //BLACKJACK_TCPUTIL_H
