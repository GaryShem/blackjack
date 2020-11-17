#include "PlayerInfo.h"
#include "Player.h"

const Hand &PlayerInfo::GetHand() const
{
    return _player->GetHand();
}

const Bet &PlayerInfo::GetBet() const
{
    return _player->GetBet();
}

int PlayerInfo::TablePosition() const
{
    return _player->TablePosition;
}
