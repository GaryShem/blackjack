#ifndef BLACKJACK_IPLAYER_H
#define BLACKJACK_IPLAYER_H

#include "CardShoe.h"
#include "ICardDealer.h"
#include "Card.h"
#include "Hand.h"
#include "PlayerDecision.h"


class IUpdatable
{
public:
    virtual void SubscribeDealer(IUpdatable* dealer) = 0;
    virtual void UnsubscribeDealer() = 0;
    virtual void PlayerUpdated(IPlayer *player) = 0;
    virtual void CardsShuffled() = 0;
    virtual void NotifyDealer(IPlayer *player) = 0;
    virtual void PlayerList(std::vector<IPlayer*> players) = 0;
};

class IPlayer : public IUpdatable
{
public:
    void AcceptCard(Card& card);
    bool IsBusted();

    virtual PlayerDecision GetDecision() = 0;
    bool HasNatural();

    Hand& GetHand();
    void ClearHand();

    virtual void Play(ICardDealer* dealer);

    int GetBet();
    void SetBet(int bet);
    void DoubleBet();

    bool GetInsurance();
    void SetInsurance(bool insurance);

    int GetBank();
    void SetBank(int bank);

    const std::string& GetName() const;
    void SetName(const std::string& name);

    const std::string& GetId() const;
    void SetId(const std::string& id);

    virtual int RequestStartingBet(int minBet, int maxBet) = 0;
    virtual bool RequestInsuranceBet() = 0;
    virtual void PayInsurance(bool dealerHasNatural);
    virtual void PayMainBet(bool dealerNatural, int dealerSum);

//    virtual void PlayerList() = 0;

    bool IsDealer() const {return _isDealer;};
    void SetDealer(bool isDealer) {_isDealer = isDealer;};

    std::string ToString();

    void SubscribeDealer(IUpdatable* player) override;
    void UnsubscribeDealer() override;
    void NotifyDealer(IPlayer *player) override;
protected:
    IUpdatable* _subscriber = nullptr;
    Hand _hand;
    int _bet = 0;
    bool _insurance = false;
    int _bank = 1000;
    std::string _name;
    std::string _id;
    bool _isDealer = false;
};

#endif //BLACKJACK_IPLAYER_H
