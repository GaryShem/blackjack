#include "Hand.h"

std::vector<Card>& Hand::Cards()
{
    //return a copy to prevent shenanigans
    return _cards;
}

int Hand::GetSum()
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

std::string Hand::ToString()
{
    std::string result;
    for (auto card : _cards)
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
