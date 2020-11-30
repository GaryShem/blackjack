#ifndef BLACKJACK_CONSOLEPLAYER_H
#define BLACKJACK_CONSOLEPLAYER_H

#include "IPlayer.h"

class ConsolePlayer : public IPlayer
{
public:
    int RequestStartingBet(int minBet, int maxBet) override;
    bool RequestInsuranceBet() override;
    PlayerDecision GetDecision() override;
    void PlayerUpdated(IPlayer* player) override;
    void CardsShuffled() override;
    void PlayerList(std::vector<IPlayer*> players) override;

    void SubscribeDealer(IUpdatable* player) override;
private:
    void PrintGameState();
    std::string GetInput();
    IPlayer* _dealer;
    std::vector<IPlayer*> _players;
};


#endif //BLACKJACK_CONSOLEPLAYER_H
