#include "IUpdater.h"

void IUpdater::Subscribe(IUpdatable *subscriber)
{
    for (auto & _subscriber : _subscribers)
    {
        if (_subscriber == subscriber)
        {
            return;
        }
    }
    _subscribers.push_back(subscriber);
}

void IUpdater::ClearSubscribers()
{
    _subscribers.clear();
}

void IUpdater::UpdateSubscribers()
{
    for (IUpdatable* subscriber : _subscribers)
    {
        subscriber->Update();
    }
}

void IUpdater::Unsubscribe(IUpdatable *subscriber)
{
    for (int i = 0; i < _subscribers.size(); i++)
    {
        if (_subscribers.at(i) == subscriber)
        {
            _subscribers.erase(_subscribers.begin() + i);
            return;
        }
    }
}
