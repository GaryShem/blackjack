#ifndef BLACKJACK_DEALER_H
#define BLACKJACK_DEALER_H

#include "IPlayer.h"
#include "IDealer.h"
#include "CardShoe.h"


class Dealer : public IDealer
{
public:
    virtual void PlayRound(std::vector<IPlayer*>& players, CardShoe &shoe) override;
    virtual void Play(IDealer* dealer, std::vector<IPlayer*>& players) override;

    virtual void UpdateGameState(IDealer* dealer, std::vector<IPlayer *> players) override;

    virtual void ReportResult(RoundResult roundResult) override;

    void DealFaceupCard(IPlayer *player) override;

protected:
    void DealFacedownCard(IPlayer *player) override;

private:
    void RevealCard();
    void ClearAllHands(std::vector<IPlayer*>& players);
    PlayerDecisions GetDecision();
    CardShoe* _shoe;
};


#endif //BLACKJACK_DEALER_H
