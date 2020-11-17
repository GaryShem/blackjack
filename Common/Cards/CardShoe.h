#ifndef BLACKJACK_CARDSHOE_H
#define BLACKJACK_CARDSHOE_H

#include "Card.h"
#include <vector>

class CardShoe
{
public:
    const int DeckCount;
    const int ShuffleThreshold;
    static const int DeckCardCount = 52;

    CardShoe(int deckCount, int shuffleThreshold);
    explicit CardShoe(int deckCount) : CardShoe(deckCount, _defaultDeckCount * DeckCardCount / 3){};
    CardShoe() : CardShoe(_defaultDeckCount, _defaultDeckCount * DeckCardCount / 3){};

    void Shuffle();
    bool IsJustShuffled();
    Card& DrawCard(bool hidden = false);
    int GetRemainingCardCount() const;
private:
    std::vector<Card> _cards;
    int _cardIndex = 0;
    static const int _defaultDeckCount = 4;
    bool _isJustShuffled;
};


#endif //BLACKJACK_CARDSHOE_H
