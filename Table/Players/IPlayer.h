#ifndef BLACKJACK_IPLAYER_H
#define BLACKJACK_IPLAYER_H

#include "CardShoe.h"
#include "Card.h"
#include "Hand.h"

enum PlayerDecisions
{
    Hit,
    Stand
};

enum RoundResult
{
    Loss,
    Win,
    Push
};

class IDealer;

class IPlayer
{
public:
    void AcceptCard(Card& card);
    bool IsBusted();
//    virtual PlayerDecisions GetPlayerDecision(Hand dealerHand, std::vector<IPlayer*> players, int playerIndex) = 0;
    virtual void UpdateGameState(IDealer* dealer, std::vector<IPlayer*> players) = 0;
    virtual void ReportResult(RoundResult roundResult) = 0;

    Hand& GetHand();
    void ClearHand();
    virtual void Play(IDealer* dealer, std::vector<IPlayer*>& players) = 0;
protected:
    Hand _hand;
};

#endif //BLACKJACK_IPLAYER_H
