#ifndef BLACKJACK_PLAYERPROXY_H
#define BLACKJACK_PLAYERPROXY_H

#include <string>
#include "Hand.h"

class PlayerProxy
{
public:
    std::string name;
    std::string id;
    int bank;
    int bet;
    bool insurance;
    Hand hand;
    bool isDealer;
};


#endif //BLACKJACK_PLAYERPROXY_H
