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
    NotifyDealer(shared_from_this());
}

int IPlayer::GetBet()
{
    return _bet;
}

void IPlayer::SetBet(int bet)
{
    _bet = bet;
    _bank -= bet;
    NotifyDealer(shared_from_this());
}

void IPlayer::DoubleBet()
{
    _bank -= _bet;
    _bet *= 2;
    NotifyDealer(shared_from_this());
}

bool IPlayer::GetInsurance()
{
    return _insurance;
}

void IPlayer::SetInsurance(bool insurance)
{
    _insurance = insurance;
    if (_insurance)
    {
        _bank -= _bet / 2;
    }
    NotifyDealer(shared_from_this());
}

int IPlayer::GetBank()
{
    return _bank;
}

void IPlayer::SetBank(int bank)
{
    _bank = bank;
    NotifyDealer(shared_from_this());
}

void IPlayer::Play(ICardDealer* cardDealer)
{
    PlayerDecision decision;
    int maxTries = 25;
    int currentTries = 0;
    while (currentTries++ < maxTries && _hand.GetSum() < 21)
    {
        if (IsBusted() || _hand.GetSum() == 21)
        {
            return;
        }

        decision = GetDecision();
        if (decision == PlayerDecision::Hit)
        {
            cardDealer->DealFaceupCard(shared_from_this());
        }
        else if (decision == PlayerDecision::Stand)
        {
            return;
        }
        else if (decision == PlayerDecision::Double)
        {
            if (_hand.Cards().size() == 2 && _bank >= _bet)
            {
                DoubleBet();
                cardDealer->DealFaceupCard(shared_from_this());
                return;
            }
            else
            {
                continue;
            }
        }
    }
    if (currentTries >= maxTries)
    {
        return;
    }
}

void IPlayer::SubscribeDealer(std::shared_ptr<IUpdatable> player)
{
    _subscriber = player;
}

void IPlayer::UnsubscribeDealer()
{
    _subscriber = nullptr;
}

void IPlayer::NotifyDealer(std::shared_ptr<IPlayer> player)
{
    if (_subscriber != nullptr)
    {
        _subscriber->PlayerUpdated(shared_from_this());
    }
}

const std::string& IPlayer::GetName() const
{
    return _name;
}

void IPlayer::SetName(const std::string& name)
{
    _name = name;
    NotifyDealer(shared_from_this());
}

const std::string& IPlayer::GetId() const
{
    return _id;
}

void IPlayer::SetId(const std::string& id)
{
    _id = id;
    NotifyDealer(shared_from_this());
}

bool IPlayer::HasNatural()
{
    return _hand.IsNatural();
}

std::string IPlayer::ToString()
{
    std::string result;
    std::string insurance = _insurance ? "true" : "false";
    if (_isDealer)
    {
        result = "Dealer: ";
        result += _hand.ToString();
    }
    else
    {
        result = "Player (" + _name + " " + _id + "): " + _hand.ToString() + " Bet: " + std::to_string(GetBet()) + ", Insurance: " + insurance;
    }
    return result;
}

void IPlayer::PayInsurance(bool dealerHasNatural)
{
    if (IsDealer())
    {
        return;
    }
    if (GetInsurance())
    {
        if (dealerHasNatural)
        {
            int pay = _bet / 2;
            pay *= 3;
            _bank += pay;
        }
        SetInsurance(false);
    }
}

void IPlayer::PayMainBet(bool dealerNatural, int dealerSum)
{

    if (IsDealer())
    {
        return;
    }
    bool playerNatural = HasNatural();
    int playerSum = _hand.GetSum();
    bool dealerBusted = dealerSum > 21;

    //someone has blackjack
    if (playerNatural || dealerNatural)
    {
        //both have blackjack
        if (playerNatural && dealerNatural)
        {
            SetBank(GetBank() + GetBet());

        }
        //player has blackjack
        else if (playerNatural)
        {
            int pay = GetBet() * 2.5;
            SetBank(GetBank() + pay);
        }
        //dealer has blackjack
        else if (dealerNatural)
        {
            //nothing
        }
    }
    //player busted
    else if (IsBusted())
    {
        //nothing
    }
    //player did not bust, dealer busted
    else if (dealerBusted)
    {
        SetBank(GetBank() + GetBet()*2);
    }
    //no bust, player has better hand
    else if (playerSum > dealerSum)
    {
        SetBank(GetBank() + GetBet()*2);
    }
    //no bust, hands of same value
    else if (playerSum == dealerSum)
    {
        SetBank(GetBank() + GetBet());
    }
    //no bust, dealer has better hand
    else if (playerSum < dealerSum)
    {
        //nothing
    }

    SetBet(0);
}




