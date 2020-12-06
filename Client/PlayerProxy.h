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
    std::vector<Hand> hands;
    bool isDealer;
};


#endif //BLACKJACK_PLAYERPROXY_H
