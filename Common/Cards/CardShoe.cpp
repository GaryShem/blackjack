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
    _isJustShuffled = false;
    return card;
}

void CardShoe::Shuffle()
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    for (auto& card : _cards)
    {
        card.Hide();
    }
    std::shuffle(_cards.begin(), _cards.end(), mt);
    _cardIndex = 0;
    _isJustShuffled = true;
}

CardShoe::CardShoe(int deckCount, int shuffleThreshold) : DeckCount(deckCount), ShuffleThreshold(shuffleThreshold)
{
    _cards.reserve(DeckCount * DeckCardCount);
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
    Shuffle();
}

int CardShoe::GetRemainingCardCount() const
{
    return _cards.size() - _cardIndex;
}

bool CardShoe::IsJustShuffled()
{
    return _isJustShuffled;
}

