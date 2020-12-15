#ifndef BLACKJACK_TCPCONSOLECLIENT_H
#define BLACKJACK_TCPCONSOLECLIENT_H


#include "TcpPlayerClient.h"

class TcpConsoleClient : public TcpPlayerClient
{
public:
    void PlayerUpdated(std::shared_ptr<PlayerProxy> player) override;
    void PlayerList(std::vector<std::shared_ptr<PlayerProxy>> players) override;
    void CardsShuffled() override;
    PlayerDecision GetDecision() override;
    int RequestStartingBet(int minBet, int maxBet) override;
    bool RequestInsuranceBet() override;
    void AskForName() override;
private:
    void PrintGameState();
};


#endif //BLACKJACK_TCPCONSOLECLIENT_H
