#include "ConsolePlayer.h"
#include "GameState.h"
#include <iostream>


void ConsolePlayer::Update()
{
    PrintGameState();
}

void ConsolePlayer::ClearBets()
{
    Player::ClearBets();
}

int ConsolePlayer::RequestStartingBet(int minBet)
{
    int bet = -1;

    bool inputCorrect = false;
    do
    {
        try
        {
            std::cout << "Your bank account: " << _bank.GetAmount() << std::endl;
            std::cout << "Please enter your starting bet, minimum " << minBet << ": ";
            std::string input = GetInput();
            bet = std::stoi(input);
            if (bet >= minBet)
            {
                if (_bank.Withdraw(bet))
                {
                    inputCorrect = true;
                }
                else
                {
                    std::cout << "Not enough money in bank, try again" << std::endl;
                }
            }
            else
            {
                std::cout << "Amount is less than minimum bet, try again" << std::endl;
            }
        }
        catch (std::exception& ex)
        {
            std::cout << "Incorrect input, try again and input an integer" << std::endl;
            inputCorrect = false;
        }
    } while (!inputCorrect);
    std::cout << "Bet accepted" << std::endl;
    _bet.Main = bet;
    return bet;
}

int ConsolePlayer::RequestInsuranceBet(int maxBet)
{
    int bet = -1;
    PrintGameState();

    int maxInsurance = _bet.Main / 2;
    if (_bank.GetAmount() < maxInsurance)
    {
        maxInsurance = _bank.GetAmount();
    }

    bool inputCorrect = false;
    do
    {
        try
        {
            std::cout << "Your bank account: " << _bank.GetAmount() << std::endl;
            std::cout << "Please enter your insurance bet, in the range of 0.." << maxInsurance << ": ";
            std::string input = GetInput();
            bet = std::stoi(input);
            if (bet >= 0 && bet <= maxBet)
            {
                if (_bank.Withdraw(bet))
                {
                    inputCorrect = true;
                }
                else
                {
                    std::cout << "Not enough money in bank, try again" << std::endl;
                }
            }
            else
            {
                std::cout << "Amount is not in acceptable range, try again" << std::endl;
            }
        }
        catch (std::exception& ex)
        {
            std::cout << "Incorrect input, try again and input an integer" << std::endl;
            inputCorrect = false;
        }
    } while (!inputCorrect);
    std::cout << "Bet accepted" << std::endl;
    _bet.Insurance = bet;
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
    std::cout << "Dealer: " << _gameState->GetDealerHand().ToString() << std::endl;
    for (auto info : _gameState->GetPlayerInfo())
    {
        std::cout << "Player " << info.GetHand().ToString() << ": " << std::endl;
    }
    std::cout << "You are Player " << TablePosition << std::endl;
}

void ConsolePlayer::PayInsurance(int amount)
{
    if (amount > 0)
    {
        std::cout << "You won insurance bet (" << amount << ")" << std::endl;
        _bank.Deposit(amount);
    }
    else
    {
        std::cout << "You lost insurance bet" << std::endl;
    }
    _bet.Insurance = 0;
}

void ConsolePlayer::PayMainBet(int amount)
{
    PrintGameState();
    if (amount == 0)
    {
        std::cout << "You lost main bet" << std::endl;
    }
    else if (amount == _bet.Main)
    {
        std::cout << "Push, your main bet (" << amount << ") is returned" << std::endl;
    }
    else if (amount > _bet.Main)
    {
        std::cout << "You won main bet (" << amount << ")" << std::endl;
    }
    else
    {
        throw std::logic_error("winning calculation error in main bet");
    }
    _bank.Deposit(amount);
    _bet.Main = 0;
}

PlayerDecisions ConsolePlayer::GetDecision()
{
    PrintGameState();
    while (true)
    {
        std::cout << "What is your decision? (hit/stand/dd): ";
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
        else if (input == "doubledown" || input == "dd")
        {
            if (_hand.Cards().size() > 2)
            {
                std::cout << "doubling down is only possible with the initial 2 cards" << std::endl;
            }
            else
            {
                return PlayerDecisions::Doubledown;
            }
        }
        else
        {
            std::cout << "incorrect input, please choose available action from the list" << std::endl;
        }
    }
}

void ConsolePlayer::ReportError(std::string message)
{
    if (message == "dd_error:money")
    {
        std::cout << "not enough money to double down" << std::endl;
    }
    else
    {
        std::cout << message << std::endl;
    }
}

