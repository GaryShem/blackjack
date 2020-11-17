#ifndef BLACKJACK_ICARDDEALER_H
#define BLACKJACK_ICARDDEALER_H

class IPlayer;

class ICardDealer
{
public:
    virtual void DealFaceupCard(IPlayer* player) = 0;
protected:
    virtual void DealFacedownCard(IPlayer* player) = 0;
};


#endif //BLACKJACK_ICARDDEALER_H
