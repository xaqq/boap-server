/* 
 * File:   Client.cpp
 * Author: xaqq
 * 
 * Created on November 3, 2013, 5:40 PM
 */

#include "Client.hpp"
#include "Log.hpp"
#include "APacket.hpp"
#include "net/ITcpProtocolHandler.hpp"
#include "Server.hpp"

Client::Client() { }

Client::~Client() { }

void Client::pushPacket(std::shared_ptr<APacket> p)
{
  std::shared_ptr<Net::ITcpProtocolHandler> handler;
  
  if (handler = tcpHandler_.lock())
    {
      DEBUG("PUSHING PACKET TO HANDLER");
      handler->pushPacket(p);
    }
}

void Client::disconnect()
{
  std::shared_ptr<Net::ITcpProtocolHandler> handler;
  
  if (handler = tcpHandler_.lock())
    {
      handler->disconnect();
    }
  Server::instance().removeClient(shared_from_this());
}