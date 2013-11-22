/* 
 * File:   SMSGCreateGame.cpp
 * Author: xaqq
 * 
 * Created on November 22, 2013, 12:24 AM
 */

#include <string>
#include "packets/SMSGCreateGame.hpp"
#include "AClient.hpp"

SMSGCreateGame::SMSGCreateGame(std::shared_ptr<AClient> source) : APacket(source) { }

SMSGCreateGame::SMSGCreateGame(const SMSGCreateGame &o) : APacket(o.source_)
{
  success_ = o.success_;
  gameUuid_ = o.gameUuid_;
  errMsg_ = o.errMsg_;
}

SMSGCreateGame::~SMSGCreateGame() { }

void SMSGCreateGame::unserialize(ByteArray) { }

int SMSGCreateGame::binaryLength() const
{
  int len = 0;
  if (success_)
    {
      len += gameUuid_.length();
    }
  else
    {
      len += errMsg_.length();
    }
  len += sizeof (unsigned char);

  return len;
}

ByteArray SMSGCreateGame::serialize() const
{
  ByteArray b;
  b.reserve(4 + errMsg_.length() + gameUuid_.length());

  b << APacket::SMSG_CREATE_GAME;
  b << binaryLength();
  if (success_)
    {
      b << '1';
      b << gameUuid_;
    }
  else
    {
      b << '0';
      b << errMsg_;
    }
  return b;
}