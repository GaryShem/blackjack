#ifndef BLACKJACK_GAMESTATE_H
#define BLACKJACK_GAMESTATE_H

#include <vector>
#include "Dealer.h"
#include "Bet.h"
#include "PlayerInfo.h"
#include "IUpdatable.h"
#include "IUpdater.h"


class GameState : public IUpdatable, public IUpdater
{
    friend Dealer;

public:
    explicit GameState(Dealer *dealer, std::vector<Player*> & players);

    const Hand& GetDealerHand() const;
    const std::vector<PlayerInfo>& GetPlayerInfo() const;
    bool IsDeckShuffled();

    void ReformPlayerInfo();

    void Update() override;
private:
    Hand _dealerHand;
    std::vector<PlayerInfo> _playerInfo;

    bool _deskShuffled;

    Dealer* _dealer;
    std::vector<Player*>& _players;
};


#endif //BLACKJACK_GAMESTATE_H
