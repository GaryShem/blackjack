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

nlohmann::json Hand::Serialize()
{
    nlohmann::json j;
    for (auto card : _cards)
    {
        j["cards"].push_back(card.Serialize());
    }
    j["hand_index"] = GetIndex();
    j["is_doubled"] = _isDoubled;
    return j;
}

bool Hand::IsSoftHand()
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
    return aceCount > 0;
}

bool Hand::IsBusted() const
{
    return GetSum() > 21;
}

bool Hand::IsDoubled()
{
    return _isDoubled;
}

void Hand::SetDoubled(bool doubled)
{
    _isDoubled = doubled;
}

int Hand::GetIndex()
{
    return _index;
}

void Hand::SetIndex(int index)
{
    _index = index;
}

Hand Hand::Split()
{
    Hand hand;
    hand.AddCard(_cards.back());
    _cards.pop_back();

    return hand;
}

Hand Hand::Deserialize(nlohmann::json json)
{
    Hand hand;
    hand.SetIndex(json["hand_index"]);
    hand.SetDoubled(json["is_doubled"]);
    for (auto& it : json["cards"])
    {
        hand.AddCard(Card::Deserialize(it.dump()));
    }
    return hand;
}

bool Hand::IsSplittable() const
{
    if (_cards.size() != 2)
    {
        return false;
    }
    int value = _cards.front().GetSoftValue();
    return std::all_of(_cards.begin(), _cards.end(), [&](auto& card) {
        return card.GetSoftValue() == value;
    });
}
