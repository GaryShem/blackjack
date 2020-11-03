#ifndef BLACKJACK_TABLE_H
#define BLACKJACK_TABLE_H

#include <Cards/CardShoe.h>
//#include "AntiCircular.h"
#include "Dealer.h"
#include "IPlayer.h"

class Table
{
public:
    explicit Table(int deckCount);
    CardShoe shoe;
    Dealer dealer;
    std::vector<IPlayer*> players;

    void AddPlayer(IPlayer* player);
    int CalculatePlayerWinnings(int playerIndex);

    [[noreturn]] void PlayGame();
};


#endif //BLACKJACK_TABLE_H
