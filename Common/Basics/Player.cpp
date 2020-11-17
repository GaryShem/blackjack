#include <stdexcept>
#include "Player.h"

void Player::ClearBets()
{
    _bet.Reset();
}

Bet &Player::GetBet()
{
    return _bet;
}

void Player::AssignGameState(GameState* state)
{
    _gameState = state;
}

void Player::Play(ICardDealer* cardDealer)
{
    PlayerDecisions decision;
    while (true)
    {
        if (IsBusted() || _hand.GetSum() == 21)
        {
            return;
        }

        decision = GetDecision();
        if (decision == PlayerDecisions::Hit)
        {
            cardDealer->DealFaceupCard(this);
        }
        else if (decision == PlayerDecisions::Stand)
        {
            return;
        }
        else if (decision == PlayerDecisions::Doubledown)
        {
            if (_hand.Cards().size() > 2)
            {
                ReportError("dd_error:cards");
            }
            bool hasEnoughMoney = _bank.Withdraw(_bet.Main);
            if (hasEnoughMoney)
            {
                _bet.Main *= 2;
                cardDealer->DealFaceupCard(this);
                return;
            }
            else
            {
                ReportError("dd_error:money");
                continue;
            }
        }
        else
        {
            throw std::logic_error("decision not supported");
        }
    }
}

void Player::ClearGameState()
{
    _gameState = nullptr;
}

Bank &Player::GetBank()
{
    return _bank;
}
