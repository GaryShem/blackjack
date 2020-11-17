#include "GameState.h"
#include "Dealer.h"
#include "Player.h"


const Hand& GameState::GetDealerHand() const
{
    return _dealer->GetHand();
}

const std::vector<PlayerInfo>& GameState::GetPlayerInfo() const
{
    return _playerInfo;
}

bool GameState::IsDeckShuffled()
{
    return _deskShuffled;
}

void GameState::Update()
{
    UpdateSubscribers();
}

GameState::GameState(Dealer* dealer, std::vector<Player*>& players) : _dealer(dealer), _players(players)
{
}

void GameState::ReformPlayerInfo()
{
    _playerInfo.clear();
    ClearSubscribers();
    for (auto player : _players)
    {
        _playerInfo.emplace_back(PlayerInfo(player));
        Subscribe(player);
    }
}

