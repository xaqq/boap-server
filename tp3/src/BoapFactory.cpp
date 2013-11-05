#include "BoapFactory.hpp"
#include "net/DefaultTcpProtocolHandler.hpp"
#include "net/TcpSession.hpp"
#include "net/UdpServer.hpp"
#include "TcpProtocolHandler.hpp"
#include "UdpProtocolHandler.hpp"
#include "Client.hpp"
#include "APacketHandler.hpp"
#include "HelloPacketHandler.hpp"

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

std::list<std::shared_ptr<APacketHandler>> BoapFactory::createPacketHandlers()
{
  std::list<std::shared_ptr<APacketHandler>> list;
  
  list.push_back(std::shared_ptr<APacketHandler>(new HelloPacketHandler()));
  
  return list;
}