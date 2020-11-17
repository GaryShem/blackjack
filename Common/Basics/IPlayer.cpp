#include "Card.h"
#include "IPlayer.h"

void IPlayer::AcceptCard(Card& card)
{
    _hand.AddCard(card);
}

bool IPlayer::IsBusted()
{
    return _hand.GetSum() > 21;
}

Hand& IPlayer::GetHand()
{
    return _hand;
}

void IPlayer::ClearHand()
{
    _hand.Clear();
}
