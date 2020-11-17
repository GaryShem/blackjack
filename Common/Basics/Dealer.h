#ifndef BLACKJACK_DEALER_H
#define BLACKJACK_DEALER_H

#include "ICardDealer.h"
#include "IPlayer.h"
#include "IUpdater.h"

class Player;

class GameState;

class Dealer : public IPlayer, public ICardDealer, public IUpdater
{
public:
    explicit Dealer(CardShoe &shoe, int minimumBet);
    virtual void PlayRound() = 0;
    virtual void PlayOwnHand() = 0;
    virtual const CardShoe &GetCardShoe();
    int GetMinimumBet();
    void DealFaceupCard(IPlayer* player) override;

protected:
    void DealFacedownCard(IPlayer* player) override;
public:
    virtual ~Dealer();
protected:
    int GetHiddenHandSum();
    CardShoe &_shoe;
    int _minimumBet;
};


#endif //BLACKJACK_EUROPEANDEALER_H
