#include "CardShoe.h"
#include <random>
#include <stdexcept>
#include <algorithm>

Card& CardShoe::DrawCard(bool hidden)
{
    if (_cardIndex >= _cards.size())
    {
        throw std::length_error("No cards left in card shoe");
    }
    Card& card = _cards.at(_cardIndex++);
    card.IsHidden = hidden;
    return card;
}

//void CardShoe::Form()
//{
//    for (int rank = Ranks::A; rank < Ranks::HiddenRank; rank++)
//    {
//        for (int suit = Suits::Spades; suit < Suits::HiddenSuit; suit++)
//        {
//            for (int deck = 0; deck < DeckCount; deck++)
//            {
//                //emplace_back creates the object in-place in the vector itself
//                //push_back would create a temporary object and then move it into vector
//                _cards.emplace_back(static_cast<Ranks>(rank), static_cast<Suits>(suit));
//            }
//        }
//    }
//}

void CardShoe::Shuffle()
{
    _cards.clear();
    for (int rank = Ranks::A; rank < Ranks::HiddenRank; rank++)
    {
        for (int suit = Suits::Spades; suit < Suits::HiddenSuit; suit++)
        {
            for (int deck = 0; deck < DeckCount; deck++)
            {
                //emplace_back creates the object in-place in the vector itself
                //push_back would create a temporary object and then move it into vector
                _cards.emplace_back(static_cast<Ranks>(rank), static_cast<Suits>(suit));
            }
        }
    }
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::shuffle(_cards.begin(), _cards.end(), mt);
}

CardShoe::CardShoe(int deckCount, int shuffleThreshold) : DeckCount(deckCount), shuffleThreshold(shuffleThreshold)
{
    _remainingCardCount = _deckCardCount * deckCount;

//    Form();
    Shuffle();
}

