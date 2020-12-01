#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include "TcpPlayerClient.h"
#include "TcpConsoleClient.h"
#include "TcpBotClient.h"

#pragma comment(lib, "Ws2_32.lib")
#include "WSAObject.h"

const int buffer_size = 1024*1024;

int main(int argc, char* argv[])
{
    WSAObject wsa;

    std::cout << "Program arguments:" << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    TcpConsoleClient client;
    client._logging = false;
    client.AskForName();
    std::string ip = "127.0.0.1";
    int port = 8005;
    std::string portString;
    if (argc >= 2)
    {
        ip = argv[1];
    }

    if (argc >= 3)
    {
        portString = argv[2];
        port = std::stoi(portString);
    }

    client.Connect(ip, port);

    bool process = true;
    while (process)
    {
        process = client.Process();
    }

    return 0;
}

