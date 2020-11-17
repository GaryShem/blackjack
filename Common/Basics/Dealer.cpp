#include "Dealer.h"
#include "GameState.h"

const CardShoe& Dealer::GetCardShoe()
{
    return _shoe;
}

Dealer::~Dealer()
{

}

Dealer::Dealer(CardShoe &shoe, int minimumBet) : _shoe(shoe), _minimumBet(minimumBet)
{

}

int Dealer::GetMinimumBet()
{
    return _minimumBet;
}

int Dealer::GetHiddenHandSum()
{
    return _hand.GetHiddenSum();
}

void Dealer::DealFaceupCard(IPlayer *player)
{
    player->AcceptCard(_shoe.DrawCard());
    UpdateSubscribers();
}

void Dealer::DealFacedownCard(IPlayer *player)
{
    player->AcceptCard(_shoe.DrawCard(true));
    UpdateSubscribers();
}


