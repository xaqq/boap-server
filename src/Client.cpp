#include "Client.hpp"
#include "Log.hpp"

Client::Client() : 
observer_(new GameObserver()),
authenticated_(false)
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

void Client::GameObserver::onClientJoined(std::shared_ptr<Game>, std::shared_ptr<Client> c)
{
  
}

void Client::GameObserver::onGameStopped(std::shared_ptr<Game>, SMSGGameStatus::Status st)
{
  
}