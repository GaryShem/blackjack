#ifndef BLACKJACK_TABLE_H
#define BLACKJACK_TABLE_H

#include <CardShoe.h>
#include "Dealer.h"
#include "TcpUtil.h"

class Table : public TcpUtil
{
public:
    explicit Table(int minBet, int maxBet);

    void AcceptTcpPlayers(int playerCount, u_short port = 8888);
    void AddPlayer(std::shared_ptr<IPlayer> player, bool assignId = true);
    void RemovePlayer(std::shared_ptr<IPlayer> player);

    void PlayGame(int roundLimit);
    std::string GenerateId();
private:
    CardShoe _shoe;
    std::vector<std::shared_ptr<IPlayer>> _players;
    std::shared_ptr<Dealer> _dealer;
    int _minimumBet;
    int _nextId = 0;

    void KickBeggars();
};


#endif //BLACKJACK_TABLE_H
