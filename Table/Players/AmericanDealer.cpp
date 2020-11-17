#include "AmericanDealer.h"
#include "Player.h"

void AmericanDealer::PlayRound()
{
    AcceptStartingBets(_minimumBet);
    DealStartingCards();
    bool hasNatural = CheckNatural();
    if (_hand.GetSum() == 11)
    {
        AcceptInsuranceBets();
    }
    PayInsurance(hasNatural);
    if (!hasNatural)
    {
        for (Player* player : _players)
        {
            player->Play(this);
        }
    }

    _hand.Reveal();
    PlayOwnHand();
    PayOut();
}

void AmericanDealer::PlayOwnHand()
{
    while (_hand.GetSum() < 17)
    {
        DealFaceupCard(this);
    }
}

void AmericanDealer::AcceptStartingBets(int minBet)
{
    for (Player* player : _players)
    {
        player->RequestStartingBet(_minimumBet);
    }
}

void AmericanDealer::DealStartingCards()
{
    for (Player* player : _players)
    {
        DealFaceupCard(player);
        DealFaceupCard(player);
    }
    DealFaceupCard(this);
    DealFacedownCard(this);
}

AmericanDealer::AmericanDealer(CardShoe &shoe, std::vector<Player*> &players, int minimumBet)
        : Dealer(shoe, minimumBet), _players(players)
{}

bool AmericanDealer::CheckNatural()
{
    bool hasNatural = Dealer::GetHiddenHandSum() == 21;
    return hasNatural;
}

void AmericanDealer::AcceptInsuranceBets()
{
    if (_hand.GetSum() == 11)
    {
        for (auto player : _players)
        {
            player->RequestInsuranceBet(player->GetBet().Main);
        }
    }
}

void AmericanDealer::PayOut()
{
    bool dealerNatural = _hand.IsNatural();
    bool dealerBust = IsBusted();
    int dealerSum = _hand.GetSum();
    for (auto player : _players)
    {
        int &mainBet = player->GetBet().Main;

        int winnings = 0;

        bool playerNatural = player->GetHand().IsNatural();
        bool playerBust = player->IsBusted();
        int playerSum = player->GetHand().GetSum();
        if (dealerNatural || playerNatural)
        {
            if (dealerNatural && playerNatural)
            {
                winnings = mainBet;
            }
            else if (dealerNatural)
            {
                winnings = 0;
            }
            else
            {
                winnings = mainBet * 2.5f;
            }
        }
        else if (playerBust)
        {
            winnings = 0;
        }
        else if (dealerBust)
        {
            winnings = mainBet * 2;
        }
        else
        {
            if (dealerSum > playerSum)
            {
                winnings = 0;
            }
            else if (dealerSum < playerSum)
            {
                winnings = mainBet * 2;
            }
            else
            {
                winnings = mainBet;
            }
        }
        player->PayMainBet(winnings);
        mainBet = 0;
    }
}

void AmericanDealer::PayInsurance(bool hasNatural)
{
    for (auto player : _players)
    {
        int &insurance = player->GetBet().Insurance;
        if (insurance == 0)
        {
            continue;
        }
        int insurancePayout = hasNatural ? insurance * 3 : 0;
        player->PayInsurance(insurancePayout);
        insurance = 0;
    }
}


