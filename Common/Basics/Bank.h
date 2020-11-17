#ifndef BLACKJACK_BANK_H
#define BLACKJACK_BANK_H


class Bank
{
public:
    Bank();
    int GetAmount() const;
    bool Withdraw(int amount);
    void Deposit(int amount);

private:
    int _amount;
};


#endif //BLACKJACK_BANK_H
