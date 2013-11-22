/* 
 * File:   MotdPacket.cpp
 * Author: xaqq
 * 
 * Created on November 7, 2013, 12:05 AM
 */

#include "Log.hpp"
#include <assert.h>
#include <string>
#include <cstring>
#include "MotdPacket.hpp"


MotdPacket::MotdPacket(std::shared_ptr<AClient> source) : APacket(source),
motd_("Default MOTD") { }

MotdPacket::~MotdPacket() { }

bool MotdPacket::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);

  return true;
}

void MotdPacket::unserialize(ByteArray) { }

ByteArray MotdPacket::serialize() const
{
  ByteArray res;
  res.resize(motd_.size());

  memcpy(&res[0], motd_.c_str(), motd_.size());
  return res;
}