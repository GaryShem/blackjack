#ifndef BLACKJACK_DEALER_H
#define BLACKJACK_DEALER_H

#include "ICardDealer.h"
#include "IPlayer.h"

class Dealer : public IPlayer, public ICardDealer
{
public:
    explicit Dealer(CardShoe &shoe, int minimumBet, int maximumBet);
    virtual ~Dealer();
    virtual void AddPlayer(std::shared_ptr<IPlayer> player);
    virtual void RemovePlayer(std::shared_ptr<IPlayer> player);
    virtual void PlayRound();
    void Play(ICardDealer* dealer) override;
    virtual const CardShoe &GetCardShoe();
    void DealFaceupCard(std::shared_ptr<IPlayer> player, int handIndex) override;

    PlayerDecision GetDecision(int handIndex) override;
    int RequestStartingBet(int minBet, int maxBet) override;
    bool RequestInsuranceBet() override;
    void PayInsurance(bool dealerHasNatural) override;
    void PayMainBet(bool dealerNatural, int dealerSum) override;
    void PlayerList(std::vector<std::shared_ptr<IPlayer>> players) override;

//    void PlayerList() override; TODO
    void PlayerUpdated(std::shared_ptr<IPlayer> player) override;

    void AcceptStartingBets(int minBet, int maxBet);
    void AcceptInsuranceBets();

    void CardsShuffled() override;

    void Shuffle();

    int _minimumBet;
    int _maximumBet;
protected:
    void DealFacedownCard(std::shared_ptr<IPlayer> player, int handIndex) override;
    void RevealHand(int handIndex = 0);
    int GetHiddenHandSum();
    CardShoe &_shoe;
    std::vector<std::shared_ptr<IPlayer>> _players;

private:
    void DealStartingCards();
    bool CheckNatural();
};


#endif //BLACKJACK_EUROPEANDEALER_H
