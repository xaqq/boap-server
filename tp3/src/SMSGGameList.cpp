/* 
 * File:   SMSGGameList.cpp
 * Author: xaqq
 * 
 * Created on November 22, 2013, 5:10 AM
 */

#include "Log.hpp"
#include "SMSGGameList.hpp"

SMSGGameList::SMSGGameList(std::shared_ptr<AClient> source) : APacket(source) { }

SMSGGameList::SMSGGameList(const SMSGGameList& orig) : APacket(source_) { }

SMSGGameList::~SMSGGameList() { }

void SMSGGameList::unserialize(ByteArray data) { }

ByteArray SMSGGameList::serialize() const
{
  ByteArray b;
  ByteArray content;

  b << SMSG_GAME_LIST;
  content = buildContent();
  b << content.size();
  b.insert(b.end(), content.begin(), content.end());

  return b;
}

ByteArray SMSGGameList::buildContent() const
{
  ByteArray b;
  b << games_.size();
  for (auto & gameInfo : games_)
    {
      b << gameInfo.first; // uuid
      b << static_cast<unsigned char>('\0');
      b << gameInfo.second.first; // game name
      b << static_cast<unsigned char>('\0');
      b << gameInfo.second.second; // nb player
    }
  return b;
}