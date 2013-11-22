/* 
 * File:   SMSGCreateGame.cpp
 * Author: xaqq
 * 
 * Created on November 22, 2013, 12:24 AM
 */

#include <string>
#include "packets/SMSGCreateGame.hpp"
#include "Log.hpp"
#include "AClient.hpp"

SMSGCreateGame::SMSGCreateGame(std::shared_ptr<AClient> source) : APacket(source) { }

SMSGCreateGame::SMSGCreateGame(const SMSGCreateGame &o) : APacket(o.source_)
{
  data_ = o.data_;
}

SMSGCreateGame::~SMSGCreateGame() { }

void SMSGCreateGame::unserialize(ByteArray) { }

ByteArray SMSGCreateGame::serialize() const
{
  ByteArray b;
  std::string msg;
  b << APacket::SMSG_CREATE_GAME;
  if (!data_.SerializeToString(&msg))
    {
      WARN("Cannot serialize: " << data_.DebugString());
      return ByteArray(0);
    }
  b << msg.length();
  b.insert(b.end(), msg.begin(), msg.end());
  return b;
}