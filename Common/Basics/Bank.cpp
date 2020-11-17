#include "Bank.h"

int Bank::GetAmount() const
{
    return _amount;
}

bool Bank::Withdraw(int amount)
{
    if (amount <= _amount)
    {
        _amount -= amount;
        return true;
    }
    else
    {
        return false;
    }
}

Bank::Bank()
{
    _amount = 1000;
}

void Bank::Deposit(int amount)
{
    _amount += amount;
}
