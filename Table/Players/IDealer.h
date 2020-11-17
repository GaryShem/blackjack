#ifndef BLACKJACK_IDEALER_H
#define BLACKJACK_IDEALER_H

#include "IPlayer.h"

class IDealer : public IPlayer
{
public:
    virtual void PlayRound(std::vector<IPlayer*>& players, CardShoe &shoe)  = 0;
    virtual void DealFaceupCard(IPlayer* player) = 0;
protected:
    virtual void DealFacedownCard(IPlayer *player) = 0;
};


#endif //BLACKJACK_IDEALER_H
