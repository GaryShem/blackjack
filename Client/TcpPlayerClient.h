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

    virtual void PlayerUpdated(std::shared_ptr<PlayerProxy> player);
    virtual void PlayerList(std::vector<std::shared_ptr<PlayerProxy>> players);
    virtual void CardsShuffled();
    virtual PlayerDecision GetDecision(int handIndex);
    virtual int RequestStartingBet(int minBet, int maxBet);
    virtual bool RequestInsuranceBet();
    void Connect(std::string ip = "127.0.0.1", u_short port = 8005);
    virtual void AskForName();
    bool Process();
    std::shared_ptr<PlayerProxy> OwnProxy();
    std::shared_ptr<PlayerProxy> Deserialize(std::string serializedPlayer);

    std::string _name;
    std::string _id;
protected:
    std::shared_ptr<PlayerProxy> _dealerProxy = nullptr;
    std::vector<std::shared_ptr<PlayerProxy>> _playerProxies;
};


#endif //BLACKJACK_TCPPLAYERCLIENT_H
