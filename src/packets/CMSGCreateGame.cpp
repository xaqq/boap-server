#include "packets/CMSGCreateGame.hpp"
#include "handlers/APacketHandler.hpp"
#include "Log.hpp"

CMSGCreateGame::CMSGCreateGame(std::shared_ptr<AClient> source) : APacket(source) { }

CMSGCreateGame::CMSGCreateGame(const CMSGCreateGame& orig) : APacket(orig)
{
  data_ = orig.data_;
}

CMSGCreateGame::~CMSGCreateGame() { }

bool CMSGCreateGame::acceptHandler(APacketHandler* handler)
{
  bool ret = true;
  ret &= APacket::acceptHandler(handler);
  ret &= handler->handle(this);

  return true;
}

void CMSGCreateGame::unserialize(ByteArray data)
{
  bool ret = data_.ParseFromArray(&data[0], data.size());
  if (!ret)
    WARN("Fail to unserialize:" << data_.DebugString());
}

ByteArray CMSGCreateGame::serialize() const
{
  return ByteArray(0);
}