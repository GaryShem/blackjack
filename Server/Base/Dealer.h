#ifndef BLACKJACK_DEALER_H
#define BLACKJACK_DEALER_H

#include "ICardDealer.h"
#include "IPlayer.h"

class Dealer : public IPlayer, public ICardDealer
{
public:
    explicit Dealer(CardShoe &shoe, int minimumBet, int maximumBet);
    virtual ~Dealer();
    virtual void AddPlayer(IPlayer* player);
    virtual void RemovePlayer(IPlayer* player);
    virtual void PlayRound();
    void Play(ICardDealer* dealer) override;
    virtual const CardShoe &GetCardShoe();
    void DealFaceupCard(IPlayer* player) override;

    PlayerDecision GetDecision() override;
    int RequestStartingBet(int minBet, int maxBet) override;
    bool RequestInsuranceBet() override;
    void PayInsurance(bool dealerHasNatural) override;
    void PayMainBet(bool dealerNatural, int dealerSum) override;
    void PlayerList(std::vector<IPlayer*> players) override;

//    void PlayerList() override; TODO
    void PlayerUpdated(IPlayer* player) override;

    void AcceptStartingBets(int minBet, int maxBet);
    void AcceptInsuranceBets();

    void CardsShuffled() override;

    void Shuffle();

    int _minimumBet;
    int _maximumBet;
protected:
    void DealFacedownCard(IPlayer* player) override;
    void RevealHand();
    int GetHiddenHandSum();
    CardShoe &_shoe;
    std::vector<IPlayer*> _players;

private:
    void DealStartingCards();
    bool CheckNatural();
};


#endif //BLACKJACK_EUROPEANDEALER_H
