#include "Dealer.h"
#include <vector>
#include <stdexcept>


void Dealer::PlayRound(std::vector<IPlayer *> &players, CardShoe &shoe)
{
    _shoe = &shoe;
    ClearAllHands(players);
    for (IPlayer *player : players)
    {
        //deal 2 cards to each player
        DealFaceupCard(player);
        DealFaceupCard(player);
    }
    //deal 2 cards to self - 1 faceup, 1 facedown
    DealFaceupCard(this);
    DealFacedownCard(this);

    //process each player's turn
    for (int i = 0; i < players.size(); i++)
    {
        IPlayer *player = players[i];
        player->Play(this, players);
    }

    Play(this, players);


    //show all players the end state of the table and report if they've won
    int dealerSum = _hand.GetSum();
    bool dealerBusted = IsBusted();
    for (int i = 0; i < players.size(); i++)
    {
        IPlayer *player = players[i];
        player->UpdateGameState(this, players);
        RoundResult roundResult;
        int playerSum = player->GetHand().GetSum();
        bool playerBusted = player->IsBusted();
        if (playerBusted)
        {
            roundResult = RoundResult::Loss;
        } else
        {
            if (dealerBusted || playerSum > dealerSum)
            {
                roundResult = RoundResult::Win;
            } else if (playerSum == dealerSum)
            {
                roundResult = RoundResult::Push;
            } else if (playerSum < dealerSum)
            {
                roundResult = RoundResult::Loss;
            } else
            {
                throw std::logic_error("unexpected round result");
            }
        }
        player->ReportResult(roundResult);
    }
}

void Dealer::RevealCard()
{
    _hand.Reveal();
}

void Dealer::ClearAllHands(std::vector<IPlayer *> &players)
{
    ClearHand();
    for (auto player : players)
    {
        player->ClearHand();
    }
}

void Dealer::UpdateGameState(IDealer *dealer, std::vector<IPlayer *> players)
{

}

void Dealer::ReportResult(RoundResult roundResult)
{

}

void Dealer::Play(IDealer *dealer, std::vector<IPlayer *> &players)
{
    //process dealer's turn
    //reveal the facedown card
    RevealCard();
    //take cards until 17
    while (GetHand().GetSum() != 21 && !IsBusted())
    {
        PlayerDecisions currentDecision = GetDecision();
        if (currentDecision == PlayerDecisions::Stand)
        {
            break;
        } else if (currentDecision == PlayerDecisions::Hit)
        {
            DealFaceupCard(this);
        }
    }
}

PlayerDecisions Dealer::GetDecision()
{
    if (_hand.GetSum() < 17)
    { return Hit; }
    else
    { return Stand; }
}

void Dealer::DealFaceupCard(IPlayer *player)
{
    player->AcceptCard(_shoe->DrawCard());
}

void Dealer::DealFacedownCard(IPlayer *player)
{
    AcceptCard(_shoe->DrawCard(true));
}
