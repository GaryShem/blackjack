#ifndef BLACKJACK_PLAYERINFO_H
#define BLACKJACK_PLAYERINFO_H


#include "Hand.h"
#include "Bet.h"
#include <vector>
#include <IUpdatable.h>

class Player;

class PlayerInfo
{
public:
    explicit PlayerInfo(Player* player) : _player(player){};
    const Hand& GetHand() const;
    const Bet& GetBet() const;
    int TablePosition() const;
private:
    Player* _player;
};


#endif //BLACKJACK_PLAYERINFO_H
