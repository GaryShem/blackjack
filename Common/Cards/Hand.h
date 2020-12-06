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
    int GetHiddenSum() const;
    bool IsBusted() const;
    bool IsNatural() const;
    void AddCard(const Card& card);
    void Reveal();
    void Clear();
    std::string ToString() const;
    bool IsSoftHand();
    bool IsDoubled();
    int GetIndex();
    void SetIndex(int index);
    void SetDoubled(bool doubled);
    bool IsSplittable() const;
    nlohmann::json Serialize();
    Hand Split();
    static Hand Deserialize(nlohmann::json json);
private:
    bool _isDoubled = false;
    int _index = 0;
    std::vector<Card> _cards;
};


#endif //BLACKJACK_HAND_H
