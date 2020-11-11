#ifndef BLACKJACK_HAND_H
#define BLACKJACK_HAND_H


#include <vector>
#include <string>
#include "Card.h"

class Hand
{
public:
    const std::vector<Card>& Cards() const;
    int GetSum() const;
    bool IsBlackjack() const;
    void AddCard(const Card& card);
    void Reveal();
    void Clear();
    std::string ToString() const;
private:
    std::vector<Card> _cards;
};


#endif //BLACKJACK_HAND_H
