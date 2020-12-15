#ifndef BLACKJACK_ICARDDEALER_H
#define BLACKJACK_ICARDDEALER_H
#include <memory>

class IPlayer;

class ICardDealer
{
public:
    virtual void DealFaceupCard(std::shared_ptr<IPlayer> player) = 0;
protected:
    virtual void DealFacedownCard(std::shared_ptr<IPlayer> player) = 0;
};


#endif //BLACKJACK_ICARDDEALER_H
