/* 
 * File:   AClient.cpp
 * Author: xaqq
 * 
 * Created on November 3, 2013, 5:43 PM
 */

#include "AClient.hpp"
#include "Log.hpp"
#include "Server.hpp"

AClient::AClient() { }

AClient::~AClient() { }

void AClient::disconnect()
{
  std::shared_ptr<Net::ATcpProtocolHandler> handler;

  if (handler = tcpHandler_.lock())
    {
      handler->disconnect();
    }
  Server::instance().removeClient(shared_from_this());
}

void AClient::disconnected()
{
  DEBUG("AClient disconnected");
  Server::instance().removeClient(shared_from_this());
}

void AClient::timeout()
{
  DEBUG("AClient udp timeout");
}

void AClient::tcpHandler(std::shared_ptr<Net::ATcpProtocolHandler> handler)
{
  tcpHandler_ = handler;
}

std::shared_ptr<Net::ATcpProtocolHandler> AClient::tcpHandler()
{
  return tcpHandler_.lock();
}

void AClient::pushPacket(std::shared_ptr<APacket> p)
{
  std::shared_ptr<Net::ATcpProtocolHandler> handler;

  if (handler = tcpHandler_.lock())
    {
      DEBUG("PUSHING PACKET TO HANDLER");
      handler->pushPacket(p);
    }
}