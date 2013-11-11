/* 
 * File:   UdpAuthHandler.cpp
 * Author: xaqq
 * 
 * Created on November 11, 2013, 3:39 PM
 */

#include "Log.hpp"
#include "UdpAuthHandler.hpp"

UdpAuthHandler::UdpAuthHandler() { }

UdpAuthHandler::UdpAuthHandler(const UdpAuthHandler& orig) { }

UdpAuthHandler::~UdpAuthHandler() { }

bool UdpAuthHandler::handle(UdpAuthPacket *p)
{
  DEBUG("Udp auth try; code is {" << p->authCode() << "}");
  // this packet has no source
  
}