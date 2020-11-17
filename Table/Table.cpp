#include "Table.h"
#include "Player.h"
#include "AmericanDealer.h"

Table::Table(int minBet) : _minimumBet(minBet)
{
    _dealer = new AmericanDealer(_shoe, _players, minBet);
    _gameState = new GameState(_dealer, _players);
}

void Table::AddPlayer(Player* player)
{
    _players.push_back(player);
    EnumeratePlayers();
    _gameState->ReformPlayerInfo();
    player->AssignGameState(_gameState);
}

void Table::RemovePlayer(int position)
{
    _players.at(position)->ClearGameState();
    _players.erase(_players.begin()+position);
    _gameState->ReformPlayerInfo();
    EnumeratePlayers();
}

[[noreturn]] void Table::PlayGame()
{
    KickBeggars();
    while (!_players.empty())
    {
        _dealer->PlayRound();
        _dealer->ClearHand();
        for (auto player : _players)
        {
            player->ClearHand();
            player->ClearBets();
        }
        KickBeggars();
    }
}

Table::~Table()
{
    for (int i = _players.size()-1; i >= 0; i--)
    {
        RemovePlayer(i);
    }
    delete(_dealer);
    delete(_gameState);
}

void Table::EnumeratePlayers()
{
    for (int i = 0; i < _players.size(); i++)
    {
        _players.at(i)->TablePosition = i;
    }
}



void Table::KickBeggars()
{
    for (int i = _players.size()-1; i >= 0; i--)
    {
        if (_players.at(i)->GetBank().GetAmount() < _minimumBet)
        {
            RemovePlayer(i);
        }
    }
}
