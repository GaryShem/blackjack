#include "TcpBotClient.h"


void TcpBotClient::PlayerUpdated(std::shared_ptr<PlayerProxy> player)
{
    TcpPlayerClient::PlayerUpdated(player);
    if (player->isDealer && player->hand.GetSum() >= 17 && !_roundCardsCounted)
    {
        AddCardsToCount();
    }
}

void TcpBotClient::PlayerList(std::vector<std::shared_ptr<PlayerProxy>> players)
{
    TcpPlayerClient::PlayerList(players);
}

void TcpBotClient::CardsShuffled()
{
    ResetRunningCount();
}

PlayerDecision TcpBotClient::GetDecision()
{
    int handValue = OwnProxy()->hand.GetSum();
    int dealerHandValue = _dealerProxy->hand.GetSum();
    bool doubleAllowed = OwnProxy()->hand.Cards().size() == 2;
    if (OwnProxy()->hand.IsSoftHand())
    {
        if (handValue <= 14)
        {
            if (dealerHandValue <= 4 || dealerHandValue >= 7)
            {
                return Hit;
            }
            else
            {
                return doubleAllowed ? Double : Hit;
            }
        }
        else if (handValue <= 16)
        {
            if (dealerHandValue <= 3 || dealerHandValue >= 7)
            {
                return Hit;
            }
            else
            {
                return doubleAllowed ? Double : Hit;
            }
        }
        else if (handValue <= 17)
        {
            if (dealerHandValue <= 2 || dealerHandValue >= 7)
            {
                return Hit;
            }
            else
            {
                return doubleAllowed ? Double : Hit;
            }
        }
        else if (handValue <= 18)
        {
            if (dealerHandValue <= 6)
            {
                return doubleAllowed ? Double : Stand;
            }
            else if (dealerHandValue <= 8)
            {
                return Stand;
            }
            else
            {
                return Hit;
            }
        }
        else if (handValue <= 19)
        {
            if (dealerHandValue == 6 && doubleAllowed)
            {
                return Double;
            }
            else
            {
                return Stand;
            }
        }
        else if (handValue <= 20)
        {
            return Stand;
        }
        else
        {
            return Stand;
        }
    }
    else
    {
        if (handValue <= 8)
        {
            return Hit;
        }
        else if (handValue <= 9)
        {
            if (dealerHandValue <= 2 || dealerHandValue >= 7)
            {
                return Hit;
            }
            else
            {
                return doubleAllowed ? Double : Hit;
            }
        }
        else if (handValue <= 10)
        {
            if (dealerHandValue <= 9)
            {
                return doubleAllowed ? Double : Hit;
            }
            else
            {
                return Hit;
            }
        }
        if (handValue <= 11)
        {
            return doubleAllowed ? Double : Hit;
        }
        else if (handValue <= 12)
        {
            if (dealerHandValue <= 3 || dealerHandValue >= 7)
            {
                return Hit;
            }
            else
            {
                return Stand;
            }
        }
        else if (handValue >= 13 && handValue <= 16)
        {
            if (dealerHandValue <= 6)
            {
                return Stand;
            }
            else
            {
                return Hit;
            }
        }
        else if (handValue >= 17)
        {
            return Stand;
        }
        else
        {
            return Stand;
        }
    }
}

int TcpBotClient::RequestStartingBet(int minBet, int maxBet)
{
    _roundCardsCounted = false;
    int bank = OwnProxy()->bank;
    int trueCount = GetTrueCount();
    int betUnitNumber = trueCount - 1;

    int bet = betUnit * betUnitNumber;
    bet = bet >= minBet ? bet : minBet;
    bet = bet <= maxBet ? bet : maxBet;
    bet = bet <= bank ? bet : bank;
    betLog[bet]++;
    return bet;
}

bool TcpBotClient::RequestInsuranceBet()
{
    return false;
}

void TcpBotClient::AskForName()
{

}

TcpBotClient::TcpBotClient() : TcpBotClient("Fwiffo")
{
//    _name = "Fwiffo_Bot"
}

TcpBotClient::TcpBotClient(std::string name)
{
    _name = name;
}

void TcpBotClient::AddCardsToCount()
{
    _roundCardsCounted = true;
    for (const auto& card : _dealerProxy->hand.Cards())
    {
        _cardsInPlay.push_back(card);
    }
    for (const auto& player : _playerProxies)
    {
        for (const auto& card : player->hand.Cards())
        {
            _cardsInPlay.push_back(card);
        }
    }
    GetRunningCount();
}

int TcpBotClient::GetRunningCount()
{
    int runningCount = 0;

    for (const auto& card : _cardsInPlay)
    {
        switch (card.Rank())
        {
            case HiddenRank:
                throw std::logic_error("server giving cards to dealer before cards are revealed");
                break;
            case _2:
            case _3:
            case _4:
            case _5:
            case _6:
                runningCount += 1;
                break;
            case _7:
            case _8:
            case _9:
                break;
            case _10:
            case J:
            case Q:
            case K:
            case A:
                runningCount -= 1;
                break;
        }
    }
    _runningCount = runningCount;
    return runningCount;
}

void TcpBotClient::ResetRunningCount()
{
    _cardsInPlay.clear();
    GetRunningCount();
}

int TcpBotClient::GetTrueCount()
{
    GetRunningCount();
    int cardsPerDeck = 52;
    int totalDecks = 4;
    int totalCards = cardsPerDeck * totalDecks;

    double cardsLeft = totalCards - _cardsInPlay.size();
    _decksRemaining = std::round(cardsLeft * 2 / cardsPerDeck) / 2;

    int trueCount = std::round(_runningCount / _decksRemaining);

    return trueCount;
}

TcpBotClient::~TcpBotClient()
{
    std::cout << "Winnings:" << OwnProxy()->bank-1000 << std::endl;
//    std::cout << "Name: " << _name << ", id == " << _id << std::endl;
//    std::cout << "Bank == " << OwnProxy()->bank << std::endl;
//    std::cout << "Bets:" << std::endl;
//    for (std::pair<const int, int>& pair : betLog)
//    {
//        std::cout << pair.first << ": " << pair.second << std::endl;
//    }
}
