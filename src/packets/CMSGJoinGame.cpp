#include "packets/CMSGJoinGame.hpp"
#include "Log.hpp"
#include "handlers/APacketHandler.hpp"

CMSGJoinGame::CMSGJoinGame(std::shared_ptr<AClient> source) : APacket(source) { }

CMSGJoinGame::CMSGJoinGame(const CMSGJoinGame& orig) : APacket(orig)
{
  data_ = orig.data_;
}

CMSGJoinGame::~CMSGJoinGame() { }

bool CMSGJoinGame::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);
  
  return true;
} 

void CMSGJoinGame::unserialize(ByteArray data)
{
  bool ret = data_.ParseFromArray(&data[0], data.size());
  if (!ret)
    {
      WARN("fail to unserialize");
    }
}

ByteArray CMSGJoinGame::serialize() const
{
  return ByteArray(0);
}