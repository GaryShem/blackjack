#ifndef BLACKJACK_HAND_H
#define BLACKJACK_HAND_H


#include <vector>
#include <string>
#include "Card.h"

class Hand
{
public:
    std::vector<Card>& Cards();
    int GetSum();
    void AddCard(const Card& card);
    void Clear();
    std::string ToString();
private:
    std::vector<Card> _cards;
};


#endif //BLACKJACK_HAND_H
