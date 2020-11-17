#ifndef BLACKJACK_PLAYER_H
#define BLACKJACK_PLAYER_H

#include "IPlayer.h"
#include "IUpdatable.h"
#include "ICardDealer.h"
#include "Bet.h"
#include "Bank.h"

class GameState;

class Player : public IPlayer, public IUpdatable
{
public:
    virtual void AssignGameState(GameState* state);
    virtual void ClearGameState();
    virtual PlayerDecisions GetDecision() = 0;
    virtual int RequestStartingBet(int minBet) = 0;
    virtual int RequestInsuranceBet(int maxBet) = 0;
    virtual void PayInsurance(int amount) = 0;
    virtual void PayMainBet(int amount) = 0;
    virtual void ClearBets();

    void Play(ICardDealer* cardDealer);
    Bet& GetBet();
    Bank& GetBank();

    virtual ~Player() = default;

    int TablePosition;

protected:
    virtual void ReportError(std::string message) = 0;
    GameState* _gameState;
    Bet _bet;
    Bank _bank;
};


#endif //BLACKJACK_PLAYER_H
