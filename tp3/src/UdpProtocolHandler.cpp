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
using namespace Net;

UdpProtocolHandler::UdpProtocolHandler(UdpServer &s, boost::asio::ip::udp::endpoint e) :
AUdpProtocolHandler(s, e) { }

UdpProtocolHandler::~UdpProtocolHandler()
{
  INFO("UDPProtocolhandler destroyed");
}

void UdpProtocolHandler::bytesAvailable(ByteArray bytes)
{
  
  if (client_)
    {
      INFO("Received udp message for client;");
      return;
    }
  /* If client isn't set, we suppose this is a authentication packet */
  std::shared_ptr<APacket>  authPacket (new UdpAuthPacket(nullptr));
  authPacket->unserialize(std::move(bytes));
  Server::instance().pushPacket(authPacket);
}