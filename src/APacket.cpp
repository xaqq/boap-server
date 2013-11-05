/* 
 * File:   APacket.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 7:10 PM
 */

#include "APacket.hpp"
#include "APacketHandler.hpp"

APacket::APacket(std::shared_ptr<AClient> source) : source_(source) { }

APacket::APacket(const APacket& orig) { }

APacket::~APacket() { }

bool APacket::acceptHandler(APacketHandler* handler)
{
  return handler->handle(this);
}

std::shared_ptr<AClient> APacket::source()
{
  return source_;
}