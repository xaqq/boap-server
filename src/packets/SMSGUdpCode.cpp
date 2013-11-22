/* 
 * File:   SMSGUdpCode.cpp
 * Author: xaqq
 * 
 * Created on November 20, 2013, 3:42 AM
 */

#include "packets/SMSGUdpCode.hpp"


SMSGUdpCode::SMSGUdpCode(std::shared_ptr<AClient> source) : APacket(source) { }

SMSGUdpCode::~SMSGUdpCode() { }

bool SMSGUdpCode::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);

  return true;
}

void SMSGUdpCode::unserialize(ByteArray)
{
  
}

ByteArray SMSGUdpCode::serialize() const
{
  ByteArray b;
  b.reserve(4 + authCode_.length());
  b << APacket::SMSG_UDP_CODE;
  b << authCode_.length();
  b << authCode_;
  return b;
}