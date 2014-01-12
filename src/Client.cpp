#include "Client.hpp"
#include "Log.hpp"

Client::Client() :
observer_(new GameObserver()),
account_(nullptr)
{
    DEBUG("Client constructed");
    udpAuthCode_ = "bla";
}

Client::~Client()
{
    DEBUG("Client destroyed");
}

const std::string &Client::udpAuthCode() const
{
    return udpAuthCode_;
}

void Client::udpAuthCode(std::string code)
{
    udpAuthCode_ = std::move(code);
}

void Client::GameObserver::onClientJoined(std::shared_ptr<AreaInstance>, std::shared_ptr<Client> c)
{

}

void Client::GameObserver::onInstanceStopped(std::shared_ptr<AreaInstance>, SMSGGameStatus::Status st)
{

}