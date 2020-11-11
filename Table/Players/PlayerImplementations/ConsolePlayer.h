#ifndef BLACKJACK_CONSOLEPLAYER_H
#define BLACKJACK_CONSOLEPLAYER_H

#include "IDealer.h"
#include "IPlayer.h"

class ConsolePlayer : public IPlayer
{
public:
    void UpdateGameState(IDealer* dealer, std::vector<IPlayer *> players) override;
    void ReportResult(RoundResult roundResult) override;
    void Play(IDealer* dealer, std::vector<IPlayer*>& players) override;
private:
    void PrintGameState(IDealer* dealer, std::vector<IPlayer *> players);
    PlayerDecisions GetDecision(IDealer* dealer, std::vector<IPlayer*>& players);
};


#endif //BLACKJACK_CONSOLEPLAYER_H
