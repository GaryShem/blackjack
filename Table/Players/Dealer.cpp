#include "Dealer.h"
#include <vector>
#include <stdexcept>

PlayerDecisions Dealer::GetPlayerDecision(Hand dealerHand, std::vector<IPlayer*> players, int playerIndex)
{
    if (_hand.GetSum() < 17)
    {
        return PlayerDecisions::Hit;
    }
    else
    {
        return PlayerDecisions::Stand;
    }
}

void Dealer::DealCard(IPlayer* player, Card &card)
{
    player->AcceptCard(card);
}

void Dealer::PlayRound(const std::vector<IPlayer*>& players, CardShoe &shoe)
{
    ClearAllHands(players);
    for (IPlayer* player : players)
    {
        //deal 2 cards to each player
        DealCard(player, shoe.DrawCard());
        DealCard(player, shoe.DrawCard());
    }
    //deal 2 cards to self - 1 faceup, 1 facedown
    DealCard(this, shoe.DrawCard());
    DealCard(this, shoe.DrawCard(true));
    //process each player's turn
    for (int i = 0; i < players.size(); i++)
    {
        IPlayer* player = players[i];
        while (player->GetHand().GetSum() != 21 && !player->IsBusted())
        {
            PlayerDecisions currentDecision = player->GetPlayerDecision(_hand, players, i);
            if (currentDecision == PlayerDecisions::Stand)
            {
                break;
            }
            else if (currentDecision == PlayerDecisions::Hit)
            {
                DealCard(player, shoe.DrawCard());
            }
        }
    }
    //process dealer's turn
    //reveal the facedown card
    RevealCard();
    //take cards until 17
    while (GetHand().GetSum() != 21 && !IsBusted())
    {
        PlayerDecisions currentDecision = GetPlayerDecision(_hand, players, -1);
        if (currentDecision == PlayerDecisions::Stand)
        {
            break;
        }
        else if (currentDecision == PlayerDecisions::Hit)
        {
            DealCard(this, shoe.DrawCard());
        }
    }
    //show all players the end state of the table and report if they've won
    int dealerSum = _hand.GetSum();
    bool dealerBusted = IsBusted();
    for (int i = 0; i < players.size(); i++)
    {
        IPlayer* player = players[i];
        player->UpdateGameState(GetHand(), players, i);
        RoundResult roundResult;
        int playerSum = player->GetHand().GetSum();
        bool playerBusted = player->IsBusted();
        if (playerBusted)
        {
            roundResult = RoundResult::Loss;
        }
        else
        {
            if (dealerBusted || playerSum > dealerSum)
            {
                roundResult = RoundResult::Win;
            }
            else if (playerSum == dealerSum)
            {
                roundResult = RoundResult::Push;
            }
            else if (playerSum < dealerSum)
            {
                roundResult = RoundResult::Loss;
            }
            else
            {
                throw std::logic_error("unexpected round result");
            }
        }
        player->ReportResult(roundResult);
    }
}

void Dealer::RevealCard()
{
    for (int i = 0; i < _hand.Cards().size(); i++)
    {
        Card& card = _hand.Cards()[i];
        card.IsHidden = false;
    }
}

void Dealer::ClearAllHands(std::vector<IPlayer *> players)
{
    _hand.Clear();
    for (auto player : players)
    {
        player->GetHand().Clear();
    }
}

void Dealer::UpdateGameState(Hand dealerHand, std::vector<IPlayer *> players, int playerIndex)
{

}

void Dealer::ReportResult(RoundResult roundResult)
{

}
