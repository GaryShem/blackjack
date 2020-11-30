#include "TcpPlayerClient.h"


#define WIN32_LEAN_AND_MEAN

#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <string>
#include <utility>
#include "Utils.h"

#pragma comment(lib, "Ws2_32.lib")

#include "WSAObject.h"
#include "json.hpp"
#include "PlayerProxy.h"

void TcpPlayerClient::PlayerUpdated(std::shared_ptr<PlayerProxy> player)
{
    if (player->isDealer)
    {
        _dealerProxy = player;
    }
    else
    {
        for (int i = 0; i < _playerProxies.size(); i++)
        {
            if (_playerProxies.at(i)->id == player->id)
            {
                _playerProxies[i] = player;
                return;
            }
        }
        _playerProxies.push_back(player);
    }
    PrintGameState();
}

void TcpPlayerClient::CardsShuffled()
{

}

PlayerDecision TcpPlayerClient::GetDecision()
{
//    PrintGameState();
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

int TcpPlayerClient::RequestStartingBet(int minBet, int maxBet)
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

bool TcpPlayerClient::RequestInsuranceBet()
{
    return false;
}

void TcpPlayerClient::Connect(std::string ip, u_short port)
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == INVALID_SOCKET)
    {
        std::cout << "coult not create sender socket, try again later" << std::endl;
        exit(123);
    }

    sockaddr_in addr;
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (connect(_socket, (sockaddr*) &addr, sizeof(addr)) == SOCKET_ERROR)
    {
        std::cout << "could not connect to target host" << std::endl;
        exit(123);
    }

    nlohmann::json j;
    j["command"] = "Authorize";
    j["data"]["name"] = _name;
    SendMsg(j.dump());

    std::string response = ReceiveMsg();
    nlohmann::json resp_j = nlohmann::json::parse(response);
    std::string command = j["command"];
    if (resp_j["command"] == "OK")
    {
        _name = resp_j["data"]["name"];
        _id = resp_j["data"]["id"];
    }
    else
    {
        std::cout << "server declined connection" << std::endl;
        exit(123);
    }
}

void TcpPlayerClient::AskForName()
{
    std::cout << "enter your name" << std::endl;
    std::getline(std::cin, _name);
}

std::shared_ptr<PlayerProxy> TcpPlayerClient::Deserialize(std::string serializedPlayer)
{
    nlohmann::json j = nlohmann::json::parse(serializedPlayer);
//    std::cout << j.dump(4) << std::endl;
    std::shared_ptr<PlayerProxy> proxy = std::make_shared<PlayerProxy>();
    proxy->isDealer = j["data"]["isDealer"];
    if (!proxy->isDealer)
    {
        proxy->name = j["data"]["name"];
        proxy->bank = j["data"]["bank"];
        proxy->insurance = j["data"]["insurance"];
        proxy->id = j["data"]["id"];
        proxy->bet = j["data"]["rate"];
    }
    for (auto it : j["data"]["hand"])
    {
        Card card = Card::Deserialize(it.dump());
        proxy->hand.AddCard(card);
    }
    return proxy;
}

bool TcpPlayerClient::Process()
{
    std::string message;
    if (!_messages.empty())
    {
        message = _messages.front();
        _messages.pop();
    }
    else
    {
        message = ReceiveMsg();
    }
    if (message.empty())
    {
        return false;
    }
    nlohmann::json j = nlohmann::json::parse(message);
    if (j["command"] == "RequestAction")
    {
        PlayerDecision decision = GetDecision();
        nlohmann::json response;
        response["command"] = "OK";
        switch (decision)
        {
            case Hit:
                response["data"]["action"] = "Hit";
                break;
            case Stand:
                response["data"]["action"] = "Stand";
                break;
            case Double:
                response["data"]["action"] = "Double";
                break;
        }
        SendMsg(response.dump());
    }
    else if (j["command"] == "Bet")
    {
        int bet = RequestStartingBet(j["data"]["min"], j["data"]["max"]);
        nlohmann::json response;
        response["command"] = "OK";
        response["data"]["bet"] = bet;
        SendMsg(response.dump());
    }

    else if (j["command"] == "Insurance")
    {
        bool insurance = RequestInsuranceBet();
        nlohmann::json response;
        response["command"] = "OK";
        response["dat"] = insurance;
        response["data"]["insurance"] = insurance;
        SendMsg(response.dump());
    }
    else if (j["command"] == "Shuffle")
    {
        CardsShuffled();
        nlohmann::json response;
        response["command"] = "OK";
        SendMsg(response.dump());
    }
    else if (j["command"] == "PlayerChanged")
    {
        nlohmann::json response;
        response["command"] = "OK";
        SendMsg(response.dump());
        PlayerUpdated(Deserialize(j.dump()));
    }
    else if (j["command"] == "PlayerList")
    {
        nlohmann::json response;
        response["command"] = "OK";
        SendMsg(response.dump());
        std::vector<std::shared_ptr<PlayerProxy>> playerList;
        for (auto it : j["data"]["Players"])
        {
            std::shared_ptr<PlayerProxy> proxy = std::make_shared<PlayerProxy>();
            proxy->name = it["name"];
            proxy->id = it["id"];
            proxy->bank = it["bank"];

            playerList.push_back(proxy);
        }
        PlayerList(playerList);
    }
    else
    {
        nlohmann::json response;
        response["command"] = "Error";
        response["desc"] = "Unknown command";
        SendMsg(response.dump());
    }
    return true;
}

std::shared_ptr<PlayerProxy> TcpPlayerClient::OwnProxy()
{
    for (auto proxy : _playerProxies)
    {
        if (proxy->id == _id)
        {
            return proxy;
        }
    }
    return nullptr;
}

void TcpPlayerClient::PrintGameState()
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

void TcpPlayerClient::PlayerList(std::vector<std::shared_ptr<PlayerProxy>> players)
{
    _playerProxies = std::move(players);
    PrintGameState();
}
