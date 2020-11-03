#ifndef BLACKJACK_CONSOLEPLAYER_H
#define BLACKJACK_CONSOLEPLAYER_H


#include "IPlayer.h"

class ConsolePlayer : public IPlayer
{
public:
    void UpdateGameState(Hand dealerHand, std::vector<IPlayer *> players, int playerIndex) override;
    PlayerDecisions GetPlayerDecision(Hand dealerHand, std::vector<IPlayer *> players, int playerIndex) override;
    void ReportResult(RoundResult roundResult) override;

private:
    void PrintGameState(Hand dealerHand, std::vector<IPlayer *> players, int playerIndex);
};


#endif //BLACKJACK_CONSOLEPLAYER_H
