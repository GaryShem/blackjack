#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H

#include <string>

enum Ranks
{
    A, _2, _3, _4, _5, _6, _7, _8, _9, _10, J, Q, K, HiddenRank
};
enum Suits
{
    Spades, Clubs, Diamonds, Hearts, HiddenSuit
};

class Card
{
public:
    Card(Ranks rank, Suits suit, bool isHidden = false) : _rank(rank), _suit(suit), IsHidden(isHidden){};
    Card(const Card& card) : Card(card._rank, card._suit, card.IsHidden) {};

    Card& operator=(Card const& card);
    int GetSoftValue();

    bool IsHidden;
    Ranks Rank();
    Suits Suit();

    std::string ToString();
private:
    Ranks _rank;
    Suits _suit;
};


#endif //BLACKJACK_CARD_H
