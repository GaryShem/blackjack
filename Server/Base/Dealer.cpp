#include "Dealer.h"

const CardShoe& Dealer::GetCardShoe()
{
    return _shoe;
}

Dealer::~Dealer()
{

}

Dealer::Dealer(CardShoe &shoe, int minimumBet, int maximumBet)
: _shoe(shoe), _minimumBet(minimumBet), _maximumBet(maximumBet)
{
    _isDealer = true;
}

int Dealer::GetHiddenHandSum()
{
    return _hand.GetHiddenSum();
}

void Dealer::DealFaceupCard(std::shared_ptr<IPlayer> player)
{
    player->AcceptCard(_shoe.DrawCard());
    PlayerUpdated(player);
//    UpdateSubscribers();
}

void Dealer::DealFacedownCard(std::shared_ptr<IPlayer> player)
{
    player->AcceptCard(_shoe.DrawCard(true));
    PlayerUpdated(player);
//    UpdateSubscribers();
}

PlayerDecision Dealer::GetDecision()
{
    if (_hand.GetSum() < 17)
    {
        return PlayerDecision::Hit;
    }
    else
    {
        return PlayerDecision::Stand;
    }
}

int Dealer::RequestStartingBet(int minBet, int maxBet)
{
    return minBet;
}

bool Dealer::RequestInsuranceBet()
{
    return false;
}

void Dealer::PayInsurance(bool dealerHasNatural)
{
    if (!IsDealer())
    {
        return;
    }
    for (auto p : _players)
    {
        p->PayInsurance(dealerHasNatural);
    }
}

void Dealer::PayMainBet(bool dealerNatural, int dealerSum)
{
    if (!IsDealer())
    {
        return;
    }
    for (auto p : _players)
    {
        p->PayMainBet(dealerNatural, dealerSum);
    }
}

void Dealer::PlayerUpdated(std::shared_ptr<IPlayer> player)
{
    if (!IsDealer())
    {
        return;
    }
    for (auto p : _players)
    {
        p->PlayerUpdated(player);
    }
}

void Dealer::Play(ICardDealer* dealer)
{
    PlayerDecision decision;
    do
    {
        decision = GetDecision();
        switch (decision)
        {

            case Hit:
                DealFaceupCard(shared_from_this());
                break;
            case Stand:
            case Double:
            default:
                break;
        }
    }
    while (!IsBusted() && decision != PlayerDecision::Stand);
}

void Dealer::AddPlayer(std::shared_ptr<IPlayer> player)
{
    _players.push_back(player);
    player->SetBank(1000);
    player->SubscribeDealer(shared_from_this());
    for (auto p_read : _players)
    {
        p_read->PlayerList(_players);
    }
}

void Dealer::RemovePlayer(std::shared_ptr<IPlayer> player)
{
    player->UnsubscribeDealer();
    _players.erase(std::find(_players.begin(), _players.end(), player));
}

void Dealer::AcceptStartingBets(int minBet, int maxBet)
{
    for (auto player : _players)
    {
        player->RequestStartingBet(minBet, maxBet);
    }
}

void Dealer::AcceptInsuranceBets()
{
    for (auto player : _players)
    {
        player->RequestInsuranceBet();
    }
}

void Dealer::RevealHand()
{
    _hand.Reveal();
    PlayerUpdated(shared_from_this());
}

void Dealer::Shuffle()
{
    _shoe.Shuffle();
    for (auto player : _players)
    {
        player->CardsShuffled();
    }
}

void Dealer::PlayRound()
{
    for (auto p_read : _players)
    {
        p_read->PlayerList(_players);
    }
    AcceptStartingBets(_minimumBet, _maximumBet);
    DealStartingCards();
    bool hasNatural = CheckNatural();
    if (_hand.GetSum() == 11)
    {
        AcceptInsuranceBets();
    }
//    AcceptInsuranceBets();
    PayInsurance(hasNatural);
    if (!hasNatural)
    {
        for (auto player : _players)
        {
            player->Play(this);
        }
        RevealHand();
        Play(this);
    }
    else
    {
        RevealHand();
    }

    PayMainBet(HasNatural(), _hand.GetSum());

    ClearHand();
    PlayerUpdated(shared_from_this());
    for (auto p : _players)
    {
        p->ClearHand();
    }

    if (_shoe.GetRemainingCardCount() < _shoe.ShuffleThreshold)
    {
        Shuffle();
    }
}

void Dealer::DealStartingCards()
{
    for (auto player : _players)
    {
        DealFaceupCard(player);
        DealFaceupCard(player);
    }
    DealFaceupCard(shared_from_this());
    DealFacedownCard(shared_from_this());
}

bool Dealer::CheckNatural()
{
    bool hasNatural = _hand.Cards().size() == 2 && Dealer::GetHiddenHandSum() == 21;
    return hasNatural;
}

void Dealer::CardsShuffled()
{

}

void Dealer::PlayerList(std::vector<std::shared_ptr<IPlayer>> players)
{

}



