#include "Table.h"

Table::Table(int deckCount) : shoe(deckCount)
{

}

void Table::AddPlayer(IPlayer* player)
{
    players.push_back(player);
}

int Table::CalculatePlayerWinnings(int playerIndex)
{
    return 0;
}

[[noreturn]] void Table::PlayGame()
{
    while (true)
    {
        dealer.PlayRound(players, shoe);
        if (shoe.GetRemainingCardCount() < shoe.ShuffleThreshold)
        {
            shoe.Shuffle();
        }
    }
}
