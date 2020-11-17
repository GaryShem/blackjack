#ifndef BLACKJACK_TABLE_H
#define BLACKJACK_TABLE_H

#include <CardShoe.h>
#include <GameState.h>
#include "Dealer.h"

class Table
{
public:
    explicit Table(int minBet);
    ~Table();

    void AddPlayer(Player* player);
    void RemovePlayer(int position);

    void PlayGame();

private:
    CardShoe _shoe;
    std::vector<Player*> _players;
    Dealer* _dealer;
    GameState* _gameState;
    int _minimumBet;

    void KickBeggars();
    void EnumeratePlayers();
};


#endif //BLACKJACK_TABLE_H
