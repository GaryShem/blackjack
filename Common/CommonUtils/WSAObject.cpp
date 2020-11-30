#include "WSAObject.h"
#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

WSAObject::WSAObject()
{
    if (WSAStartup(MAKEWORD(1,1), &wsaData) != 0)
    {
        exit(1);
    }
}

WSAObject::~WSAObject()
{
    WSACleanup();
}
