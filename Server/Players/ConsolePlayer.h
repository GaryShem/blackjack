#ifndef BLACKJACK_CONSOLEPLAYER_H
#define BLACKJACK_CONSOLEPLAYER_H

#include "IPlayer.h"

class ConsolePlayer : public IPlayer
{
public:
    int RequestStartingBet(int minBet, int maxBet) override;
    bool RequestInsuranceBet() override;
    PlayerDecision GetDecision() override;
    void PlayerUpdated(std::shared_ptr<IPlayer> player) override;
    void CardsShuffled() override;
    void PlayerList(std::vector<std::shared_ptr<IPlayer>> players) override;

    void SubscribeDealer(std::shared_ptr<IUpdatable> player) override;
private:
    void PrintGameState();
    std::string GetInput();
    std::shared_ptr<IPlayer> _dealer;
    std::vector<std::shared_ptr<IPlayer>> _players;
};


#endif //BLACKJACK_CONSOLEPLAYER_H
