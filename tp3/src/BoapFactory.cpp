#include "BoapFactory.hpp"
#include "net/TcpSession.hpp"
#include "net/UdpServer.hpp"
#include "TcpProtocolHandler.hpp"
#include "UdpProtocolHandler.hpp"
#include "Client.hpp"
#include "APacketHandler.hpp"
#include "HelloPacketHandler.hpp"
#include "net/AUdpProtocolHandler.hpp"
#include "TcpProtocolHandler.hpp"
#include "net/ATcpProtocolHandler.hpp"
#include "AdminTcpHandler.hpp"
#include "UdpAuthHandler.hpp"
#include "AuthPacketHandler.hpp"
#include "CreateGameHandler.hpp"

std::shared_ptr<Net::ATcpProtocolHandler> BoapFactory::createTcpAdminProtocolHandler()
{
  return std::shared_ptr<Net::ATcpProtocolHandler > (new Net::AdminTcpHandler());
}

std::shared_ptr<Net::ATcpProtocolHandler> BoapFactory::createTcpProtocolHandler()
{
  return std::shared_ptr<Net::ATcpProtocolHandler > (new Net::TcpProtocolHandler());
}

std::shared_ptr<Net::AUdpProtocolHandler> BoapFactory::createUdpProtocolHandler(Net::UdpServer &s, boost::asio::ip::udp::endpoint e)
{
  return std::shared_ptr<Net::AUdpProtocolHandler > (new Net::UdpProtocolHandler(s, e));
}

std::shared_ptr<AClient> BoapFactory::createClient()
{
  return std::shared_ptr<AClient > (new Client());
}

std::list<std::shared_ptr<APacketHandler >> BoapFactory::createPacketHandlers()
{
  std::list < std::shared_ptr < APacketHandler >> list;

  list.push_back(std::shared_ptr<APacketHandler > (new HelloPacketHandler()));
  list.push_back(std::shared_ptr<APacketHandler > (new UdpAuthHandler()));
  list.push_back(std::shared_ptr<APacketHandler > (new AuthPacketHandler()));
  list.push_back(std::shared_ptr<APacketHandler > (new CreateGameHandler()));

  return list;
}