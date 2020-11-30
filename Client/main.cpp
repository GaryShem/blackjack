#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include "TcpPlayerClient.h"

#pragma comment(lib, "Ws2_32.lib")
#include "WSAObject.h"

const int buffer_size = 1024*1024;

int main(int argc, char* argv[])
{
    WSAObject wsa;

    TcpPlayerClient client;
    client.AskForName();
//    client._name = "net";
    client.Connect();

    bool process = true;
    while (process)
    {
        process = client.Process();
    }

    return 0;
}

