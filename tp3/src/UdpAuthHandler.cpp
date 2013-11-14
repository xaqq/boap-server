/* 
 * File:   UdpAuthHandler.cpp
 * Author: xaqq
 * 
 * Created on November 11, 2013, 3:39 PM
 */

#include "Log.hpp"
#include "UdpAuthHandler.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Scheduler.hpp"
#include "UdpProtocolHandler.hpp"

UdpAuthHandler::UdpAuthHandler() { }

UdpAuthHandler::UdpAuthHandler(const UdpAuthHandler& orig) { }

UdpAuthHandler::~UdpAuthHandler() { }

bool UdpAuthHandler::handle(UdpAuthPacket *p)
{
  DEBUG("Udp auth try; code is {" << p->authCode() << "}");
  // this packet has no source

  for (auto abstractClientPtr : Server::instance().clients())
    {
      auto clientPtr = std::dynamic_pointer_cast<Client > (abstractClientPtr);

      if (clientPtr && clientPtr->udpHandler() == nullptr &&
          clientPtr->udpAuthCode() == p->authCode())
        {
          clientPtr->udpHandler(p->handler());
          Scheduler::instance()->runInUdpThread(
                                                std::bind([](std::shared_ptr<Net::UdpProtocolHandler> handler, std::shared_ptr<Client> client)
          {
                                                          handler->client(client);
          }, std::static_pointer_cast<Net::UdpProtocolHandler > (p->handler()), clientPtr));
          break;
        }
    }
  return true;
}