#include <iostream>
#include "TcpPlayerClient.h"
#include "TcpConsoleClient.h"
#include "TcpBotClient.h"

int main(int argc, char* argv[])
{
    std::cout << "Program arguments:" << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    TcpBotClient client;
//    client._logging = false;
    client.AskForName();
    std::string ip = "127.0.0.1";
    int port = 8005;
    std::string portString;
    if (argc >= 3)
    {
        ip = argv[2];
    }

    if (argc >= 4)
    {
        portString = argv[3];
        port = std::stoi(portString);
    }

    client.Connect(ip, port);

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    try
    {
        bool process = true;
        while (process)
        {
            process = client.Process();
        }
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        throw;
    }

    return 0;
}

