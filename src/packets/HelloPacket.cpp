/* 
 * File:   HelloPacket.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 8:45 PM
 */

#include <assert.h>
#include "packets/HelloPacket.hpp"


HelloPacket::HelloPacket(std::shared_ptr<AClient> source) : APacket(source) { }

HelloPacket::~HelloPacket() { }

bool HelloPacket::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);
  
  return true;
} 

void HelloPacket::unserialize(ByteArray data)
{
}

ByteArray HelloPacket::serialize() const
{
  return ByteArray(0);
}