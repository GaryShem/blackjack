#include "ConsolePlayer.h"
#include <iostream>
#include "Dealer.h"

int ConsolePlayer::RequestStartingBet(int minBet, int maxBet)
{
    int bet = -1;

    if (_bank < maxBet)
    {
        maxBet = _bank;
    }

    bool inputCorrect = false;
    do
    {
        try
        {
            std::cout << "Your bank account: " << _bank << std::endl;
            std::cout << "Please enter your starting bet, minimum " << minBet << ", maximum " << maxBet << ": ";
            std::string input = GetInput();
            bet = std::stoi(input);
            if (bet >= minBet && bet <= maxBet)
            {
                inputCorrect = true;
                SetBet(bet);
            }
            else
            {
                std::cout << "Invalid bet value, try again" << std::endl;
            }
        }
        catch (std::exception& ex)
        {
            std::cout << "Incorrect input, try again and input an integer" << std::endl;
            inputCorrect = false;
        }
    } while (!inputCorrect);
    std::cout << "Bet accepted" << std::endl;
    _bet = bet;
    return bet;
}

bool ConsolePlayer::RequestInsuranceBet()
{
    int bet = -1;
    int insurance = _bet / 2;
    PrintGameState();

    if (_bank < insurance)
    {
        return false;
    }


    bool inputCorrect = false;
    do
    {
        std::cout << "Your bank account: " << _bank << std::endl;
        std::cout << "Do you want to make insurance bet of " << insurance << " ? (y/n): ";
        std::string input = GetInput();
        if (input == "y")
        {
            inputCorrect = true;
            SetInsurance(true);
        }
        else if (input == "n")
        {
            inputCorrect = true;
            _insurance = false;
        }
    } while (!inputCorrect);
    std::cout << "Bet accepted" << std::endl;
    return bet;
}

std::string ConsolePlayer::GetInput()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsolePlayer::PrintGameState()
{
    std::cout << std::endl;
    std::cout << _dealer->ToString() << std::endl;
    for (auto player : _players)
    {
        std::cout << player->ToString() << std::endl;
    }
    std::cout << "You are Player (" << _name << ", " << _id << ")" << std::endl;
}

PlayerDecision ConsolePlayer::GetDecision()
{
    PrintGameState();
    while (true)
    {
        std::cout << "What is your decision? (hit/stand/dd): ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "hit")
        {
            return PlayerDecision::Hit;
        }
        else if (input == "stand")
        {
            return PlayerDecision::Stand;
        }
        else if (input == "double" || input == "dd")
        {
            if (_hand.Cards().size() > 2)
            {
                std::cout << "doubling down is only possible with the initial 2 cards" << std::endl;
            }
            else
            {
                return PlayerDecision::Double;
            }
        }
        else
        {
            std::cout << "incorrect input, please choose available action from the list" << std::endl;
        }
    }
}

void ConsolePlayer::PlayerUpdated(std::shared_ptr<IPlayer> player)
{
    if (player->IsDealer())
    {
        if (_dealer != player)
        {
            _dealer = player;
        }
    }
    else if (std::find(_players.begin(), _players.end(), player) == _players.end())
    {
        _players.push_back(player);
    }
    PrintGameState();
}

void ConsolePlayer::CardsShuffled()
{

}

void ConsolePlayer::SubscribeDealer(std::shared_ptr<IUpdatable> player)
{
    IPlayer::SubscribeDealer(player);
    _dealer = std::dynamic_pointer_cast<Dealer>(player);
}

void ConsolePlayer::PlayerList(std::vector<std::shared_ptr<IPlayer>> players)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (i >= _players.size() || _players[i] != players[i])
        {
            _players[i] = players[i];
        }
    }
}


