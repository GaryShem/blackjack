#ifndef BLACKJACK_TCPPLAYERSERVER_H
#define BLACKJACK_TCPPLAYERSERVER_H

#define WIN32_LEAN_AND_MEAN
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include "IPlayer.h"
#include "PlayerDecision.h"
#include "TcpUtil.h"

#pragma comment(lib, "Ws2_32.lib")
#include "WSAObject.h"

class TcpPlayerServer : public IPlayer, public TcpUtil
{
public:
    static const int buffer_size = 1024*1024;
    static const int port = 8080;

    explicit TcpPlayerServer(SOCKET socket);

    void PlayerUpdated(std::shared_ptr<IPlayer> player) override;
    void CardsShuffled() override;
    PlayerDecision GetDecision() override;
    int RequestStartingBet(int minBet, int maxBet) override;
    bool RequestInsuranceBet() override;
    void PlayerList(std::vector<std::shared_ptr<IPlayer>> players) override;

    ~TcpPlayerServer();
private:
    nlohmann::json Serialize(std::shared_ptr<IPlayer> player);

    char* _buf = new char[buffer_size];
};


#endif //BLACKJACK_TCPPLAYERSERVER_H
