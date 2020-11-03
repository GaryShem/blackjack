#include "Card.h"

Card& Card::operator=(const Card &card)
{
    if (this != &card)
    {
        _rank = card._rank;
        _suit = card._suit;
        IsHidden = card.IsHidden;
    }
    return *this;
}

int Card::GetSoftValue()
{
    if (IsHidden)
    {
        return 0;
    }

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

Ranks Card::Rank()
{
    return _rank;
}

Suits Card::Suit()
{
    return _suit;
}

std::string Card::ToString()
{
    std::string result;
    std::string rank;
    std::string suit;

    //if the card is facedown, don't show rank or suit
    if (IsHidden)
    {
        result = "??";
        return result;
    }

    //otherwise form rank/suit combination

    //get rank
    switch (_rank)
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
    switch (_suit)
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
