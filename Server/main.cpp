#include <iostream>
#include "Table.h"
#include "ConsolePlayer.h"
#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <Utils.h>
#include "Players/TcpPlayerServer.h"
#include "json.hpp"

#pragma comment(lib, "Ws2_32.lib")
#include "WSAObject.h"


int main(int argc, char *argv[])
{
    WSAObject wsa;

    std::cout << "Program arguments:" << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    if (argc < 2)
    {
        std::cout << "Pass in TCP player count as first program argument (argv[1])" << std::endl;
    }

    int playerLimit = std::stoi(std::string(argv[1]));

    std::string portString;
    int port = 8005;
    if (argc >= 3)
    {
        portString = argv[2];
        port = std::stoi(portString);
    }

    Table table(10, 100);
    table.AcceptTcpPlayers(playerLimit, port);
    table.PlayGame(5);

    return 0;
}

