#include "CMSGGameList.hpp"
#include "AClient.hpp"
#include "APacketHandler.hpp"

CMSGGameList::CMSGGameList(std::shared_ptr<AClient> src) : APacket(src) { }

CMSGGameList::CMSGGameList(const CMSGGameList &o) : APacket(o.source_) { }


bool CMSGGameList::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);
  
  return true;
} 


void CMSGGameList::unserialize(ByteArray data) { }

ByteArray CMSGGameList::serialize() const
{
  ByteArray b;
  return b;
}
