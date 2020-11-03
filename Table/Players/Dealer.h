#ifndef BLACKJACK_DEALER_H
#define BLACKJACK_DEALER_H

#include "IPlayer.h"
#include "CardShoe.h"


class Dealer : public IPlayer
{
public:
    PlayerDecisions GetPlayerDecision(Hand dealerHand, std::vector<IPlayer*> players, int playerIndex) override;
    void PlayRound(const std::vector<IPlayer*>& players, CardShoe &shoe);

    void UpdateGameState(Hand dealerHand, std::vector<IPlayer *> players, int playerIndex) override;

    void ReportResult(RoundResult roundResult) override;

private:
    void DealCard(IPlayer* player, Card& card);
    void RevealCard();
    void ClearAllHands(std::vector<IPlayer*> players);
};


#endif //BLACKJACK_DEALER_H
