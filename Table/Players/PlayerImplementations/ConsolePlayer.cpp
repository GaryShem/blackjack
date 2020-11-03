#include "ConsolePlayer.h"
#include <iostream>

PlayerDecisions ConsolePlayer::GetPlayerDecision(Hand dealerHand, std::vector<IPlayer *> players, int playerIndex)
{
    PrintGameState(dealerHand, players, playerIndex);

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
    return PlayerDecisions::Stand;
}

void ConsolePlayer::PrintGameState(Hand dealerHand, std::vector<IPlayer *> players, int playerIndex)
{
    std::cout << std::endl;
    std::cout << "Dealer: " << dealerHand.ToString() << std::endl;
    for (int i = 0; i < players.size(); i++)
    {
        IPlayer* player = players[i];
        std::cout << "Player " << i << ": " << player->GetHand().ToString() << std::endl;
    }
    std::cout << "You are Player " << playerIndex << std::endl;
}

void ConsolePlayer::UpdateGameState(Hand dealerHand, std::vector<IPlayer *> players, int playerIndex)
{
    PrintGameState(dealerHand, players, playerIndex);
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
