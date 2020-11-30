#ifndef BLACKJACK_WSAOBJECT_H
#define BLACKJACK_WSAOBJECT_H

#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

class WSAObject
{
public:
    WSAObject();
    ~WSAObject();
private:
    WSADATA wsaData;
};


#endif //BLACKJACK_WSAOBJECT_H
