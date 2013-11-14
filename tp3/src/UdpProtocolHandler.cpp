/* 
 * File:   UdpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 30, 2013, 1:33 AM
 */

#include <boost/asio.hpp>
#include "UdpProtocolHandler.hpp"
#include "Log.hpp"
#include "Scheduler.hpp"
#include "UdpAuthHandler.hpp"
#include <thread>
#include "Server.hpp"
#include "Client.hpp"

using namespace Net;

UdpProtocolHandler::UdpProtocolHandler(UdpServer &s, boost::asio::ip::udp::endpoint e) :
AUdpProtocolHandler(s, e) { }

UdpProtocolHandler::~UdpProtocolHandler()
{
  INFO("UDPProtocolhandler destroyed");
  if (client_)
    client_->timeout();
}

void UdpProtocolHandler::bytesAvailable(ByteArray bytes)
{

  if (client_)
    {
      INFO("Received udp message for client;");
      return;
    }
  /* If client isn't set, we suppose this is a authentication packet */
  UdpAuthPacket *authPacket = new UdpAuthPacket(nullptr);
  authPacket->unserialize(std::move(bytes));
  authPacket->handler(shared_from_this());
  std::shared_ptr<APacket> authPacketPtr(authPacket);
  Server::instance().pushPacket(authPacketPtr);
}

void UdpProtocolHandler::client(std::shared_ptr<Client> c)
{
  client_ = c;
}

std::shared_ptr<Client> UdpProtocolHandler::client()
{
  return client_;
}