#ifndef BLACKJACK_IUPDATER_H
#define BLACKJACK_IUPDATER_H

#include <vector>
#include "IUpdatable.h"

class IUpdater
{
public:
    virtual void Subscribe(IUpdatable* subscriber);
    virtual void Unsubscribe(IUpdatable* subscriber);
    virtual void ClearSubscribers();
    virtual void UpdateSubscribers();
protected:
    std::vector<IUpdatable*> _subscribers;
};


#endif //BLACKJACK_IUPDATER_H
