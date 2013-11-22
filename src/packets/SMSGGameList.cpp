/* 
 * File:   SMSGGameList.cpp
 * Author: xaqq
 * 
 * Created on November 22, 2013, 5:10 AM
 */

#include "Log.hpp"
#include "packets/SMSGGameList.hpp"

SMSGGameList::SMSGGameList(std::shared_ptr<AClient> source) : APacket(source) { }

SMSGGameList::SMSGGameList(const SMSGGameList& orig) : APacket(source_) { }

SMSGGameList::~SMSGGameList() { }

void SMSGGameList::unserialize(ByteArray data) { }

ByteArray SMSGGameList::serialize() const
{
  ByteArray b;
  std::string msg;

  b << SMSG_GAME_LIST;
  if (!data_.SerializeToString(&msg))
    {
      WARN("Cannot serialize: " << data_.DebugString());
      return ByteArray(0);
    }
  b << msg.length();
  b.insert(b.end(), msg.begin(), msg.end());
  return b;
}
