#include <Utils.h>
#include <iostream>
#include "json.hpp"
#include "TcpPlayerServer.h"


TcpPlayerServer::TcpPlayerServer(SOCKET socket)
{
    _socket = socket;
}

void TcpPlayerServer::PlayerUpdated(std::shared_ptr<IPlayer> player)
{
    nlohmann::json j;
    j["command"] = "PlayerChanged";

    j["data"] = Serialize(player);
    SendMsg(j.dump());
    ReceiveMsg();
}

void TcpPlayerServer::CardsShuffled()
{
    nlohmann::json j;
    j["command"] = "Shuffle";
    SendMsg(j.dump());
    ReceiveMsg();
}

PlayerDecision TcpPlayerServer::GetDecision()
{
    nlohmann::json j;
    j["command"] = "RequestAction";
    SendMsg(j.dump());
    std::string message = ReceiveMsg();
    nlohmann::json response = nlohmann::json::parse(message);
    if (response["data"]["action"] == "Hit")
    {
        return PlayerDecision::Hit;
    }
    else if (response["data"]["action"] == "Stand")
    {
        return PlayerDecision::Stand;
    }
    else if (response["data"]["action"] == "Double")
    {
        return PlayerDecision::Double;
    }
    else
    {
        return PlayerDecision::Stand;
    }
}

int TcpPlayerServer::RequestStartingBet(int minBet, int maxBet)
{
    for (int tries = 0; tries < 25; tries++)
    {
        nlohmann::json j;
        if (_bank < maxBet)
        {
            maxBet = _bank;
        }
        j["command"] = "Bet";
        j["data"]["min"] = minBet;
        j["data"]["max"] = maxBet;
        SendMsg(j.dump());
        std::string message = ReceiveMsg();
        nlohmann::json response = nlohmann::json::parse(message);
        int bet = response["data"]["bet"];
        if (bet >= minBet && bet <= maxBet)
        {
            SetBet(bet);
            return bet;
        }
    }
    return minBet;
}

bool TcpPlayerServer::RequestInsuranceBet()
{
    for (int tries = 0; tries < 25; tries++)
    {
        nlohmann::json j;
        if (_bank < _bet / 2)
        {
            return false;
        }
        j["command"] = "Insurance";
        SendMsg(j.dump());
        std::string message = ReceiveMsg();
        nlohmann::json response_json = nlohmann::json::parse(message);
        bool response_insurance = response_json["data"]["insurance"].get<bool>();
        SetInsurance(response_insurance);
        return _insurance;
    }
    return false;
}

nlohmann::json TcpPlayerServer::Serialize(std::shared_ptr<IPlayer> player)
{
    nlohmann::json j;
    j["name"] = player->GetName();
    j["isDealer"] = player->IsDealer();
    j["id"] = player->GetId();
    j["rate"] = player->GetBet();
    j["insurance"] = player->GetInsurance();
    j["bank"] = player->GetBank();
    j["hand"] = player->GetHand().Serialize();

    return j;
}

TcpPlayerServer::~TcpPlayerServer()
{
    delete[] _buf;
    closesocket(_socket);
}

void TcpPlayerServer::PlayerList(std::vector<std::shared_ptr<IPlayer>> players)
{
    nlohmann::json j;
    j["command"] = "PlayerList";
    for (auto player : players)
    {
        nlohmann::json playerJson;
        playerJson["name"] = player->GetName();
        playerJson["id"] = player->GetId();
        playerJson["bank"] = player->GetBank();

        j["data"]["Players"].push_back(playerJson);
    }
    SendMsg(j.dump());

    ReceiveMsg();
}
