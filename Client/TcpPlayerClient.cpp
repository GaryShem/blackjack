#include "TcpPlayerClient.h"

#include <iostream>
#include <string>
#include <utility>
#include "Utils.h"
#include "json.hpp"
#include "PlayerProxy.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void TcpPlayerClient::Connect(std::string ip, u_short port)
{
    _context = std::make_shared<boost::asio::io_context>();
    _socket = std::make_shared<tcp::socket>(*_context);

    tcp::resolver resolver(*_context);
    boost::asio::connect(*_socket, resolver.resolve(ip, std::to_string(port)));

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
        std::cerr << "server declined connection" << std::endl;
        exit(123);
    }
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
}

void TcpPlayerClient::PlayerList(std::vector<std::shared_ptr<PlayerProxy>> players)
{
    _playerProxies = players;
}

void TcpPlayerClient::CardsShuffled()
{

}

bool TcpPlayerClient::RequestInsuranceBet()
{
    return false;
}

int TcpPlayerClient::RequestStartingBet(int minBet, int maxBet)
{
    return minBet;
}

PlayerDecision TcpPlayerClient::GetDecision()
{
    return Stand;
}

void TcpPlayerClient::AskForName()
{
    _name = "base_tcp_bot";
}
