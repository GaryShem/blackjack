#ifndef BLACKJACK_TCPBOTCLIENT_H
#define BLACKJACK_TCPBOTCLIENT_H

#include "TcpPlayerClient.h"

class TcpBotClient : public TcpPlayerClient
{
public:
    TcpBotClient();
    explicit TcpBotClient(std::string name);
    void PlayerUpdated(std::shared_ptr<PlayerProxy> player) override;
    void PlayerList(std::vector<std::shared_ptr<PlayerProxy>> players) override;
    void CardsShuffled() override;
    PlayerDecision GetDecision() override;
    int RequestStartingBet(int minBet, int maxBet) override;
    bool RequestInsuranceBet() override;
    void AskForName() override;
};


#endif //BLACKJACK_TCPBOTCLIENT_H
