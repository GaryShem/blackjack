#include "Table.h"

#include <Utils.h>
#include <iostream>
#include "Players/TcpPlayerServer.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

Table::Table(int minBet, int maxBet)
{
    _minimumBet = minBet;
    _dealer = std::make_shared<Dealer>(_shoe, minBet, maxBet);
}

void Table::AddPlayer(std::shared_ptr<IPlayer> player, bool assignId)
{
    if (assignId)
    {
        player->SetId(GenerateId());
    }
    _dealer->AddPlayer(player);
    _players.push_back(player);
}

void Table::RemovePlayer(std::shared_ptr<IPlayer> player)
{
    _dealer->RemovePlayer(player);
    _players.erase(std::find(_players.begin(), _players.end(), player));
}

void Table::PlayGame(int roundLimit)
{
    int currentRound = 0;
    while (_players.size() > 0 && currentRound++ < roundLimit)
    {
        if (currentRound % 100 == 0)
        {
            std::cout << "Round " << currentRound << std::endl;
        }
        KickBeggars();
        _dealer->PlayRound();
        KickBeggars();
    }
}

void Table::KickBeggars()
{
    for (int i = _players.size() - 1; i >= 0; i--)
    {
        if (_players.at(i)->GetBank() < _minimumBet)
        {
            RemovePlayer(_players.at(i));
        }
    }
}

std::string Table::GenerateId()
{
    return std::to_string(_nextId++);
}

void Table::AcceptTcpPlayers(int playerCount, u_short port)
{
//    boost::asio::io_context io_context;
    _context = std::make_shared<boost::asio::io_context>();
    tcp::acceptor acceptor(*_context, tcp::endpoint(tcp::v4(), port));

    for (int i = 0; i < playerCount; i++)
    {
        _socket = std::make_shared<tcp::socket>(*_context);
        acceptor.accept(*_socket);

        std::string authMessage = ReceiveMsg();
        nlohmann::json j = nlohmann::json::parse(authMessage);
        if (j["command"] == "Authorize" && !j["data"]["name"].empty())
        {
            std::shared_ptr<TcpPlayerServer> player = std::make_shared<TcpPlayerServer>(_socket);
            player->_logging = _logging;
            player->SetName(j["data"]["name"]);
            player->SetId(GenerateId());

            nlohmann::json response;
            response["command"] = "OK";
            response["data"]["name"] = player->GetName();
            response["data"]["id"] = player->GetId();
            response["data"]["Bank"] = player->GetBank();
            player->SendMsg(response.dump());
            AddPlayer(player, false);
        }
        else
        {
            nlohmann::json response;
            response["command"] = "Error";
            if (j["command"] != "Authorize")
            {
                response["data"]["description"] = "Unknown command, Authorize expected";
            }
            else if (j["data"]["name"].empty())
            {
                response["data"]["description"] = "Name cannot be empty";
            }
            else
            {
                response["data"]["description"] = "Unknown error";
            }
            std::string message = response.dump();
            SendMsg(message);
        }
    }
}
