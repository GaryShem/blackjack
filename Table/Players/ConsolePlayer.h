#ifndef BLACKJACK_CONSOLEPLAYER_H
#define BLACKJACK_CONSOLEPLAYER_H

#include "Player.h"

class ConsolePlayer : public Player
{
public:
    void Update() override;
    void ClearBets() override;
    int RequestStartingBet(int minBet) override;
    int RequestInsuranceBet(int maxBet) override;
    void PayInsurance(int amount) override;
    void PayMainBet(int amount) override;
    PlayerDecisions GetDecision() override;
protected:
    void ReportError(std::string message) override;
private:
    void PrintGameState();
    std::string GetInput();
};


#endif //BLACKJACK_CONSOLEPLAYER_H
