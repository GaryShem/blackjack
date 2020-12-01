#include "TcpBotClient.h"


void TcpBotClient::PlayerUpdated(std::shared_ptr<PlayerProxy> player)
{
    TcpPlayerClient::PlayerUpdated(player);
}

void TcpBotClient::PlayerList(std::vector<std::shared_ptr<PlayerProxy>> players)
{
    TcpPlayerClient::PlayerList(players);
}

void TcpBotClient::CardsShuffled()
{

}

PlayerDecision TcpBotClient::GetDecision()
{
    int handValue = OwnProxy()->hand.GetSum();
    int dealerHandValue = _dealerProxy->hand.GetSum();
    if (handValue <= 11)
    {
        return PlayerDecision::Hit;
    }
    else if (handValue == 12)
    {
        if (dealerHandValue > 3 && dealerHandValue < 7)
        {
            return Stand;
        }
        else
        {
            return Hit;
        }
    }
    else if (handValue > 12 && handValue < 17)
    {
        if (dealerHandValue < 7)
        {
            return Stand;
        }
        else
        {
            return Hit;
        }
    }
    else
    {
        return Stand;
    }
}

int TcpBotClient::RequestStartingBet(int minBet, int maxBet)
{
    return minBet;
}

bool TcpBotClient::RequestInsuranceBet()
{
    return false;
}

void TcpBotClient::AskForName()
{

}

TcpBotClient::TcpBotClient() : TcpBotClient("Fwiffo_Bot")
{
//    _name = "Fwiffo_Bot"
}

TcpBotClient::TcpBotClient(std::string name)
{
    _name = name;
}
