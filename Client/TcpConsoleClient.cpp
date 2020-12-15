#include "TcpConsoleClient.h"

void TcpConsoleClient::PrintGameState()
{
    std::cout << std::endl;
    if (_dealerProxy != nullptr)
    {
        std::cout << "Dealer: " << _dealerProxy->hand.ToString() << std::endl;
    }
    for (auto proxy : _playerProxies)
    {
        std::cout << "Player (" << proxy->name << ", " << proxy->id << ")" << proxy->hand.ToString() << std::endl;
        std::cout << "Bet: " << proxy->bet << " Insurance: " << (proxy->insurance ? "true" : "false") << " Bank: "
                  << proxy->bank << std::endl;
    }
    std::shared_ptr<PlayerProxy> ownProxy = OwnProxy();
    if (ownProxy != nullptr)
    {
        std::cout << "You are Player (" << OwnProxy()->name << ", " << OwnProxy()->id << ")" << std::endl;
    }
}

void TcpConsoleClient::PlayerUpdated(std::shared_ptr<PlayerProxy> player)
{
    TcpPlayerClient::PlayerUpdated(player);
    PrintGameState();
}

void TcpConsoleClient::PlayerList(std::vector<std::shared_ptr<PlayerProxy>> players)
{
    TcpPlayerClient::PlayerList(players);
    PrintGameState();
}

void TcpConsoleClient::CardsShuffled()
{

}

PlayerDecision TcpConsoleClient::GetDecision()
{
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
            if (OwnProxy()->hand.Cards().size() > 2)
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
    return Stand;
}

int TcpConsoleClient::RequestStartingBet(int minBet, int maxBet)
{
    int bet = -1;

    auto ownProxy = OwnProxy();
    int bank = ownProxy->bank;

    if (ownProxy->bank < maxBet)
    {
        maxBet = bank;
    }

    bool inputCorrect = false;
    do
    {
        try
        {
            std::cout << "Your bank account: " << bank << std::endl;
            std::cout << "Please enter your starting bet, minimum " << minBet << ", maximum " << maxBet << ": ";
            std::string input;
            std::getline(std::cin, input);
            bet = std::stoi(input);
            if (bet >= minBet && bet <= maxBet)
            {
                inputCorrect = true;
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
    return bet;
}

bool TcpConsoleClient::RequestInsuranceBet()
{
    bool bet = false;


    bool inputCorrect = false;
    do
    {
        std::cout << "Do you want to insure your bet? (y/n)";
        std::string input;
        std::getline(std::cin, input);
        if (input == "y")
        {
            inputCorrect = true;
            bet = true;
        }
        else if (input == "n")
        {
            inputCorrect = true;
            bet = false;
        }
        else
        {
            std::cout << "Invalid bet value, try again" << std::endl;
        }
    } while (!inputCorrect);
    return bet;

    return false;
}

void TcpConsoleClient::AskForName()
{
    std::cout << "enter your name" << std::endl;
    std::getline(std::cin, _name);
}
