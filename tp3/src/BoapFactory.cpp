#include "BoapFactory.hpp"
#include "net/DefaultTcpProtocolHandler.hpp"
#include "net/TcpSession.hpp"
#include "net/UdpServer.hpp"
#include "TcpProtocolHandler.hpp"
#include "UdpProtocolHandler.hpp"
#include "Client.hpp"

std::shared_ptr<Net::ITcpProtocolHandler> BoapFactory::createTcpProtocolHandler(Net::TcpSession &session)
{
  return std::shared_ptr<Net::ITcpProtocolHandler> (new Net::TcpProtocolHandler(session));
}

std::shared_ptr<Net::IUdpProtocolHandler> BoapFactory::createUdpProtocolHandler(Net::UdpServer &s,  boost::asio::ip::udp::endpoint e)
{
  return std::shared_ptr<Net::IUdpProtocolHandler> (new Net::UdpProtocolHandler(s, e));
}

std::shared_ptr<AClient> BoapFactory::createClient()
{
  return std::shared_ptr<AClient> (new Client());
}