#include "ConsolePlayer.h"
#include <iostream>


void ConsolePlayer::PrintGameState(IDealer* dealer, std::vector<IPlayer *> players)
{
    std::cout << std::endl;
    std::cout << "Dealer: " << dealer->GetHand().ToString() << std::endl;
    int playerIndex = -1;
    for (int i = 0; i < players.size(); i++)
    {
        IPlayer* player = players[i];
        if (player == this)
        {
            playerIndex = i;
        }
        std::cout << "Player " << i << ": " << player->GetHand().ToString() << std::endl;
    }
    std::cout << "You are Player " << playerIndex << std::endl;
}

void ConsolePlayer::UpdateGameState(IDealer* dealer, std::vector<IPlayer *> players)
{
    PrintGameState(dealer, players);
}

void ConsolePlayer::ReportResult(RoundResult roundResult)
{
    std::string message;
    switch (roundResult)
    {

        case Loss:
            message = "YOU LOST";
            break;
        case Win:
            message = "YOU WON";
            break;
        case Push:
            message = "YOU TIED";
            break;
    }
    std::cout << std::endl << message << std::endl;
}

void ConsolePlayer::Play(IDealer *dealer, std::vector<IPlayer *> &players)
{
    PlayerDecisions decision;
    do
    {
        PrintGameState(dealer, players);
        decision = GetDecision(dealer, players);
        switch (decision)
        {

            case Hit:
                dealer->DealFaceupCard(this);
                break;
            case Stand:
                break;
            default:
                throw std::exception("unprocessed player decision");
                break;
        }
    }
    while (!IsBusted() && decision != PlayerDecisions::Stand);
}

PlayerDecisions ConsolePlayer::GetDecision(IDealer *dealer, std::vector<IPlayer *> &players)
{
    while (true)
    {
        std::cout << "What is your decision? (hit/stand): ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "hit")
        {
            return PlayerDecisions::Hit;
        }
        else if (input == "stand")
        {
            return PlayerDecisions::Stand;
        }
        else
        {
            std::cout << "incorrect input, please choose hit or stand" << std::endl;
        }
    }
}
