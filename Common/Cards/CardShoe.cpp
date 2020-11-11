#include "CardShoe.h"
#include <random>
#include <stdexcept>
#include <algorithm>

Card &CardShoe::DrawCard(bool hidden)
{
    if (_cardIndex >= _cards.size())
    {
        throw std::length_error("No cards left in card shoe");
    }
    Card &card = _cards.at(_cardIndex++);
    if (!hidden)
    {
        card.Reveal();
    }
    return card;
}

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
                _cards.emplace_back(static_cast<Ranks>(rank), static_cast<Suits>(suit), true);
            }
        }
    }
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::shuffle(_cards.begin(), _cards.end(), mt);
    _cardIndex = 0;
}

CardShoe::CardShoe(int deckCount, int shuffleThreshold) : DeckCount(deckCount), ShuffleThreshold(shuffleThreshold)
{

    Shuffle();
}

int CardShoe::GetRemainingCardCount() const
{
    return _cards.size() - _cardIndex;
}

