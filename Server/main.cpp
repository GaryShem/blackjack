#include <iostream>
#include "Table.h"
#include <Utils.h>

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "Program arguments:" << std::endl;
        for (int i = 0; i < argc; i++)
        {
            std::cout << argv[i] << std::endl;
        }

        if (argc < 2)
        {
            std::cout << "Pass in TCP player count as first program argument (argv[1])" << std::endl;
            return 1;
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
        table.PlayGame(1000);

    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        throw;
    }

    return 0;
}

