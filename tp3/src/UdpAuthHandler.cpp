/* 
 * File:   UdpAuthHandler.cpp
 * Author: xaqq
 * 
 * Created on November 11, 2013, 3:39 PM
 */

#include "Log.hpp"
#include "UdpAuthHandler.hpp"
#include "Server.hpp"

UdpAuthHandler::UdpAuthHandler() { }

UdpAuthHandler::UdpAuthHandler(const UdpAuthHandler& orig) { }

UdpAuthHandler::~UdpAuthHandler() { }

bool UdpAuthHandler::handle(UdpAuthPacket *p)
{
  DEBUG("Udp auth try; code is {" << p->authCode() << "}");
  // this packet has no source
  
  for (auto abstractClientPtr : Server::instance()->clients())
    {
      auto clientPtr = std::dynamic_pointer_cast<Client>(clientPtr);
      if (clientPtr && clientPtr->udpHandler() == nullptr && 
          clientPtr->udpAuthCode() == p->authCode())
        {
          client->udpHandler(p->handler());
          break;
        }
    }
  return true;
}