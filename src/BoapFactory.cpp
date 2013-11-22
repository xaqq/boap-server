#include "BoapFactory.hpp"

#include "net/TcpProtocolHandler.hpp"
#include "net/UdpProtocolHandler.hpp"
#include "net/AdminTcpHandler.hpp"

#include "handlers/APacketHandler.hpp"
#include "handlers/UdpAuthHandler.hpp"
#include "handlers/AuthPacketHandler.hpp"
#include "handlers/CreateGameHandler.hpp"
#include "handlers/GameListHandler.hpp"
#include "handlers/HelloPacketHandler.hpp"

#include "Client.hpp"

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
  list.push_back(std::shared_ptr<APacketHandler > (new GameListHandler()));

  return list;
}