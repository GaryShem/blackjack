#include "Card.h"
#include "json.hpp"

Card& Card::operator=(const Card& card)
{
    if (this != &card)
    {
        _rank = card._rank;
        _suit = card._suit;
        _isHidden = card._isHidden;
    }
    return *this;
}

int Card::GetSoftValue() const
{
    if (_isHidden)
    {
        return 0;
    }
    return GetHiddenSoftValue();
}

Ranks Card::Rank() const
{
    if (_isHidden)
    {
        return Ranks::HiddenRank;
    }
    else
    {
        return _rank;
    }
}

Suits Card::Suit() const
{
    if (_isHidden)
    {
        return Suits::HiddenSuit;
    }
    else
    {
        return _suit;
    }
}

std::string Card::ToString() const
{
    std::string result;
    std::string rank;
    std::string suit;

    //get rank
    switch (Rank())
    {
        case A:
            rank = "A";
            break;
        case _2:
            rank = "2";
            break;
        case _3:
            rank = "3";
            break;
        case _4:
            rank = "4";
            break;
        case _5:
            rank = "5";
            break;
        case _6:
            rank = "6";
            break;
        case _7:
            rank = "7";
            break;
        case _8:
            rank = "8";
            break;
        case _9:
            rank = "9";
            break;
        case _10:
            rank = "10";
            break;
        case J:
            rank = "J";
            break;
        case Q:
            rank = "Q";
            break;
        case K:
            rank = "K";
            break;
        case HiddenRank:
        default:
            rank = "?";
            break;
    }

    //get suit
    switch (Suit())
    {

        case Spades:
            suit = "s";
            break;
        case Clubs:
            suit = "c";
            break;
        case Diamonds:
            suit = "d";
            break;
        case Hearts:
            suit = "h";
            break;
        case HiddenSuit:
        default:
            suit = "?";
            break;
    }

    //combine rank and suit
    result = rank + suit;
    return result;
}

void Card::Hide()
{
    _isHidden = true;
}

void Card::Reveal()
{
    _isHidden = false;
}

bool Card::IsHidden() const
{
    return _isHidden;
}

bool Card::operator==(const Card& rhs) const
{
    return _isHidden == rhs._isHidden &&
           _rank == rhs._rank &&
           _suit == rhs._suit;
}

bool Card::operator!=(const Card& rhs) const
{
    return !(rhs == *this);
}

int Card::GetHiddenSoftValue() const
{
    int result = 0;
    switch (_rank)
    {
        case A:
            result = 11;
            break;
        case _2:
            result = 2;
            break;
        case _3:
            result = 3;
            break;
        case _4:
            result = 4;
            break;
        case _5:
            result = 5;
            break;
        case _6:
            result = 6;
            break;
        case _7:
            result = 7;
            break;
        case _8:
            result = 8;
            break;
        case _9:
            result = 9;
            break;
        case _10:
        case J:
        case Q:
        case K:
            result = 10;
            break;
        case HiddenRank:
            result = 0;
            break;
    }
    return result;
}

nlohmann::json Card::Serialize()
{
    nlohmann::json j;
    j["isOpen"] = !_isHidden;
    j["value"] = SerializeRank();
    j["suit"] = SerializeSuit();
    return j;
}

std::string Card::SerializeRank() const
{
    switch (Rank())
    {
        case A:
            return "Ace";
            break;
        case _2:
            return "2";
            break;
        case _3:
            return "3";
            break;
        case _4:
            return "4";
            break;
        case _5:
            return "5";
            break;
        case _6:
            return "6";
            break;
        case _7:
            return "7";
            break;
        case _8:
            return "8";
            break;
        case _9:
            return "9";
            break;
        case _10:
            return "10";
            break;
        case J:
            return "Jack";
            break;
        case Q:
            return "Queen";
            break;
        case K:
            return "King";
            break;
        case HiddenRank:
            return "Hidden";
            break;
    }
    return "";
}

std::string Card::SerializeSuit() const
{
    switch (Suit())
    {
        case Spades:
            return "Spades";
            break;
        case Clubs:
            return "Clubs";
            break;
        case Diamonds:
            return "Diamonds";
            break;
        case Hearts:
            return "Hearts";
            break;
        case HiddenSuit:
            return "Hidden";
            break;
    }
    return "";
}

Ranks Card::DeserializeRank(std::string rank)
{
    std::map<std::string, Ranks> rankMap;
    rankMap.insert(std::pair<std::string, Ranks>("2", _2));
    rankMap.insert(std::pair<std::string, Ranks>("3", _3));
    rankMap.insert(std::pair<std::string, Ranks>("4", _4));
    rankMap.insert(std::pair<std::string, Ranks>("5", _5));
    rankMap.insert(std::pair<std::string, Ranks>("6", _6));
    rankMap.insert(std::pair<std::string, Ranks>("7", _7));
    rankMap.insert(std::pair<std::string, Ranks>("8", _8));
    rankMap.insert(std::pair<std::string, Ranks>("9", _9));
    rankMap.insert(std::pair<std::string, Ranks>("10", _10));
    rankMap.insert(std::pair<std::string, Ranks>("Jack", J));
    rankMap.insert(std::pair<std::string, Ranks>("Queen", Q));
    rankMap.insert(std::pair<std::string, Ranks>("King", K));
    rankMap.insert(std::pair<std::string, Ranks>("Ace", A));
    rankMap.insert(std::pair<std::string, Ranks>("Hidden", HiddenRank));

    return rankMap[rank];
}

Suits Card::DeserializeSuit(std::string suit)
{
    std::map<std::string, Suits> suitMap;
    suitMap.insert(std::pair<std::string, Suits>("Spades", Spades));
    suitMap.insert(std::pair<std::string, Suits>("Clubs", Clubs));
    suitMap.insert(std::pair<std::string, Suits>("Hearts", Hearts));
    suitMap.insert(std::pair<std::string, Suits>("Diamonds", Diamonds));
    suitMap.insert(std::pair<std::string, Suits>("Hidden", HiddenSuit));
    return suitMap[suit];
}

Card Card::Deserialize(std::string serializedCard)
{
    nlohmann::json j = nlohmann::json::parse(serializedCard);
    bool isHidden = !j["isOpen"];
    if (isHidden)
    {
        return Card(HiddenRank, HiddenSuit, true);
    }
    else
    {
        return Card(DeserializeRank(j["value"]), DeserializeSuit(j["suit"]), false);
    }
}



