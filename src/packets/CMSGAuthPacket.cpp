#include "packets/CMSGAuthPacket.hpp"
#include "Log.hpp"
#include "handlers/APacketHandler.hpp"

CMSGAuthPacket::CMSGAuthPacket(std::shared_ptr<AClient> source) : APacket(source) { }

CMSGAuthPacket::CMSGAuthPacket(const CMSGAuthPacket& orig) : APacket(orig)
{
  data_ = orig.data_;
}

CMSGAuthPacket::~CMSGAuthPacket() { }

bool CMSGAuthPacket::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);

  return true;
}

void CMSGAuthPacket::unserialize(ByteArray data)
{

  bool ret = data_.ParseFromArray(&data[0], data.size());
  if (!ret)
    {
      WARN("Invalid packet: " << data_.DebugString());
      return;
    }
}

ByteArray CMSGAuthPacket::serialize() const
{
  return ByteArray(0);
}