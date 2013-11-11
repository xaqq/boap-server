/* 
 * File:   Client.cpp
 * Author: xaqq
 * 
 * Created on November 3, 2013, 5:40 PM
 */

#include "Client.hpp"
#include "Log.hpp"
#include "APacket.hpp"
#include "net/ATcpProtocolHandler.hpp"
#include "Server.hpp"
#include "UdpAuthHandler.hpp"

Client::Client()
{
  DEBUG("Client constructed");
}

Client::~Client()
{
  DEBUG("Client destroyed");
}

const std::string &Client::udpAuthCode() const
{
  return udpAuthCode_;
}