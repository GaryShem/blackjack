#ifndef BLACKJACK_AMERICANDEALER_H
#define BLACKJACK_AMERICANDEALER_H

#include "Dealer.h"

class AmericanDealer : public Dealer
{
public:
    AmericanDealer(CardShoe &shoe, std::vector<Player *> &players, int minimumBet);

    void PlayRound() override;
    void PlayOwnHand() override;

private:
    std::vector<Player*>& _players;

    void AcceptStartingBets(int minBet);
    void AcceptInsuranceBets();
    void DealStartingCards();
    bool CheckNatural();
    void PayInsurance(bool hasNatural);
    void PayOut();
};


#endif //BLACKJACK_AMERICANDEALER_H
