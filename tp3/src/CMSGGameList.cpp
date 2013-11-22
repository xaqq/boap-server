#include "CMSGGameList.hpp"

CMSGGameList::CMSGGameList(const CMSGGameList &o) : APacket(o.source_){ }

void CMSGGameList::unserialize(ByteArray data) { }

ByteArray CMSGGameList::serialize()
{
  ByteArray b;
  return b;
}
