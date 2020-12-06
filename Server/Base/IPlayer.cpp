#include <sstream>
#include "Card.h"
#include "IPlayer.h"

void IPlayer::AcceptCard(Card& card, int handIndex)
{
    if (_hands.empty() && handIndex == 0)
    {
        _hands.emplace_back();
    }
    _hands[handIndex].AddCard(card);
}

bool IPlayer::IsBusted(int handIndex)
{
    return _hands[handIndex].IsBusted();
}

Hand& IPlayer::GetHand(int handIndex)
{
    return _hands[handIndex];
}

void IPlayer::ClearHand()
{
    _hands.clear();
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

void IPlayer::DoubleBet(int handIndex)
{
    _bank -= _bet;
    _hands[handIndex].SetDoubled(true);
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
    for (int handIndex = 0; handIndex < _hands.size(); handIndex++)
    {
        PlayerDecision decision;
        int maxTries = 25;
        int currentTries = 0;
        while (currentTries++ < maxTries)
        {
            Hand& hand = _hands[handIndex];
            if (hand.IsBusted() || hand.GetSum() == 21)
            {
                break;
            }

            decision = GetDecision(handIndex);
            if (decision == PlayerDecision::Hit)
            {
                cardDealer->DealFaceupCard(shared_from_this(), handIndex);
            }
            else if (decision == PlayerDecision::Stand)
            {
                break;
            }
            else if (decision == PlayerDecision::Double)
            {
                if (hand.Cards().size() == 2 && _bank >= _bet)
                {
                    DoubleBet(handIndex);
                    cardDealer->DealFaceupCard(shared_from_this(), handIndex);
                    break;
                }
                else
                {
                    continue;
                }
            }
            else if (decision == PlayerDecision::Split)
            {
                if (GetBank() >= GetBet())
                {
                    _hands.push_back(hand.Split());
                    _hands.back().SetIndex(_hands.size()-1);
                    SetBank(GetBank() - GetBet());
                    cardDealer->DealFaceupCard(shared_from_this(), handIndex);
                    cardDealer->DealFaceupCard(shared_from_this(), _hands.size() - 1);
                }
            }
        }
        if (currentTries >= maxTries)
        {
            continue;
        }
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

bool IPlayer::HasNatural(int handIndex)
{
    return _hands[handIndex].IsNatural();
}

std::string IPlayer::ToString()
{
    std::string result;
    std::string insurance = _insurance ? "true" : "false";
    std::ostringstream strings;
    if (_isDealer)
    {
        strings << "Dealer: ";
    }
    else
    {
        strings << "Player (" + _name + " " + _id + "), Bet (" + std::to_string(GetBet()) + "), Insurance: (" + insurance + ")" << std::endl;
    }
    for (int i = 0; i < _hands.size(); i++)
    {
        strings << "Hand " + std::to_string(i) + ": " + _hands[i].ToString() << std::endl;
    }
    result = strings.str();
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
    bool dealerBusted = dealerSum > 21;
    int totalBankChange = 0;
    for (int handIndex = 0; handIndex < _hands.size(); handIndex++)
    {
        Hand& hand = _hands[handIndex];
        int handBankChange = 0;
        bool playerNatural = hand.IsNatural() && _hands.size() == 1;
        int playerSum = hand.GetSum();

        //someone has blackjack
        if (playerNatural || dealerNatural)
        {
            //both have blackjack
            if (playerNatural && dealerNatural)
            {
                handBankChange += GetBet();

            }
                //player has blackjack
            else if (playerNatural)
            {
                handBankChange += GetBet() * 2.5;
            }
                //dealer has blackjack
            else if (dealerNatural)
            {
                //nothing
            }
        }
            //player busted
        else if (hand.IsBusted())
        {
            //nothing
        }
            //player did not bust, dealer busted
        else if (dealerBusted)
        {
            handBankChange += GetBet() * 2;
        }
            //no bust, player has better hand
        else if (playerSum > dealerSum)
        {
            handBankChange += GetBet() * 2;
        }
            //no bust, hands of same value
        else if (playerSum == dealerSum)
        {
            handBankChange = GetBet();
        }
        //no bust, dealer has better hand
        else if (playerSum < dealerSum)
        {
            //nothing
        }
        if (hand.IsDoubled())
        {
            handBankChange *= 2;
        }
        totalBankChange += handBankChange;
    }
    if (totalBankChange != 0)
    {
        SetBank(GetBank() + totalBankChange);
    }
    SetBet(0);
}





