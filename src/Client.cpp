#include "Client.hpp"
#include "Log.hpp"

Client::Client() : authenticated_(false)
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