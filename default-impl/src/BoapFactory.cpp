#include "BoapFactory.hpp"
#include "net/DefaultTcpProtocolHandler.hpp"
#include "net/DefaultUdpProtocolHandler.hpp"
#include "net/TcpSession.hpp"

std::shared_ptr<Net::ITcpProtocolHandler> BoapFactory::createTcpProtocolHandler(Net::TcpSession &session)
{
  return std::shared_ptr<Net::ITcpProtocolHandler> (new Net::DefaultTcpProtocolHandler(session));
}

std::shared_ptr<Net::IUdpProtocolHandler> BoapFactory::createUdpProtocolHandler(Net::UdpServer &s)
{
  return std::shared_ptr<Net::IUdpProtocolHandler> (new Net::DefaultUdpProtocolHandler(s));
}