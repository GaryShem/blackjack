#include "Hand.h"
#include "json.hpp"

const std::vector<Card>& Hand::Cards() const
{
    //return const reference to prevent random errors
    return _cards;
}

int Hand::GetSum() const
{
    int aceCount = 0;
    int result = 0;
    for (auto &card : _cards)
    {
        result += card.GetSoftValue();
        if (card.Rank() == Ranks::A)
        {
            aceCount++;
        }
    }
    while (result > 21 && aceCount > 0)
    {
        result -= 10;
        aceCount--;
    }
    return result;
}

void Hand::AddCard(const Card& card)
{
    _cards.push_back(card);
}

std::string Hand::ToString() const
{
    std::string result;
    for (const Card& card : _cards)
    {
        if (result.empty())
        {
            result = card.ToString();
        }
        else
        {
            result = result + "_" + card.ToString();
        }
    }
    result = result + " (" + std::to_string(GetSum()) + ")";
    return result;
}

void Hand::Clear()
{
    _cards.clear();
}

void Hand::Reveal()
{
    for (auto& card : _cards)
    {
        card.Reveal();
    }
}

bool Hand::IsNatural() const
{
    return GetSum() == 21 && _cards.size() == 2;
}

int Hand::GetHiddenSum() const
{
    int result = 0;
    for (auto card : _cards)
    {
        result += card.GetHiddenSoftValue();
    }
    return result;
}

Card& Hand::DrawCard()
{
    Card& card = _cards.back();
    _cards.pop_back();
    return card;
}

nlohmann::json Hand::Serialize()
{
    nlohmann::json j;
    for (auto card : _cards)
    {
        j.push_back(card.Serialize());
    }
    return j;
}
