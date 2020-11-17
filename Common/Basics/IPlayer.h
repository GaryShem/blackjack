#ifndef BLACKJACK_IPLAYER_H
#define BLACKJACK_IPLAYER_H

#include "CardShoe.h"
#include "Card.h"
#include "Hand.h"

enum PlayerDecisions
{
    Hit,
    Stand,
    Doubledown,
    Split
};

enum RoundResult
{
    Loss,
    Win,
    Push
};

class IPlayer
{
public:
    void AcceptCard(Card& card);
    bool IsBusted();

    Hand& GetHand();
    void ClearHand();
protected:
    Hand _hand;
};

#endif //BLACKJACK_IPLAYER_H
