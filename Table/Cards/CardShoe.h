#ifndef BLACKJACK_CARDSHOE_H
#define BLACKJACK_CARDSHOE_H

#include "Card.h"
#include <vector>

class CardShoe
{
public:
    const int DeckCount;
    const int shuffleThreshold;

    CardShoe(int deckCount, int shuffleThreshold);
    explicit CardShoe(int deckCount) : CardShoe(deckCount, _defaultDeckCount * _deckCardCount / 3){};
    CardShoe() : CardShoe(_defaultDeckCount, _defaultDeckCount * _deckCardCount / 3){};

//    void Form();
    void Shuffle();
    Card& DrawCard(bool hidden = false);
    int GetRemainingCardCount() const {return _remainingCardCount;};
private:
    std::vector<Card> _cards;
    int _remainingCardCount;
    int _cardIndex = 0;
    static const int _deckCardCount = 52;
    static const int _defaultDeckCount = 4;
};


#endif //BLACKJACK_CARDSHOE_H
