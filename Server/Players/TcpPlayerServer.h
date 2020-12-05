#ifndef BLACKJACK_TCPPLAYERSERVER_H
#define BLACKJACK_TCPPLAYERSERVER_H

#include "IPlayer.h"
#include "PlayerDecision.h"
#include "TcpUtil.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpPlayerServer : public IPlayer, public TcpUtil
{
public:
    explicit TcpPlayerServer(std::shared_ptr<tcp::socket> socket);

    void PlayerUpdated(std::shared_ptr<IPlayer> player) override;
    void CardsShuffled() override;
    PlayerDecision GetDecision() override;
    int RequestStartingBet(int minBet, int maxBet) override;
    bool RequestInsuranceBet() override;
    void PlayerList(std::vector<std::shared_ptr<IPlayer>> players) override;
private:
    nlohmann::json Serialize(std::shared_ptr<IPlayer> player);
};


#endif //BLACKJACK_TCPPLAYERSERVER_H
