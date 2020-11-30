#ifndef BLACKJACK_TCPPLAYERCLIENT_H
#define BLACKJACK_TCPPLAYERCLIENT_H

#include "PlayerProxy.h"
#include "PlayerDecision.h"
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <string>
#include <queue>
#include "TcpUtil.h"

#pragma comment(lib, "Ws2_32.lib")

class TcpPlayerClient : public TcpUtil
{
public:
    const int buffer_size = 1024*1024;

    void PlayerUpdated(PlayerProxy* player);
    void PlayerList(std::vector<PlayerProxy*> players);
    void CardsShuffled();
    PlayerDecision GetDecision();
    int RequestStartingBet(int minBet, int maxBet);
    bool RequestInsuranceBet();
    void Connect(std::string ip = "127.0.0.1", u_short port = 8888);
    void AskForName();
    bool Process();
    PlayerProxy* OwnProxy();
    PlayerProxy* Deserialize(std::string serializedPlayer);


    ~TcpPlayerClient();
    std::string _name;
    std::string _id;
private:
    PlayerProxy* _dealerProxy = nullptr;
    std::vector<PlayerProxy*> _playerProxies;
    void PrintGameState();
};


#endif //BLACKJACK_TCPPLAYERCLIENT_H
