#ifndef BLACKJACK_TABLE_H
#define BLACKJACK_TABLE_H

#include <CardShoe.h>
#include "Dealer.h"
#include "TcpUtil.h"

class Table : TcpUtil
{
public:
    explicit Table(int minBet, int maxBet);
    ~Table();

    void AcceptTcpPlayers(int playerCount);
    void AddPlayer(IPlayer* player);
    void RemovePlayer(IPlayer* player);

    void PlayGame(int roundLimit);
    std::string GenerateId();
private:
    CardShoe _shoe;
    std::vector<IPlayer*> _players;
    Dealer* _dealer;
    int _minimumBet;
    int _nextId = 0;

    void KickBeggars();
};


#endif //BLACKJACK_TABLE_H
