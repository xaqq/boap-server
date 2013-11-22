#include "packets/CMSGJoinGame.hpp"
#include "Log.hpp"
#include "handlers/APacketHandler.hpp"

CMSGJoinGame::CMSGJoinGame(std::shared_ptr<AClient> source) : APacket(source) { }

CMSGJoinGame::CMSGJoinGame(const CMSGJoinGame& orig) : APacket(orig)
{
  gameUuid_ = orig.gameUuid_;
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
   std::string uuid(data.begin(), data.end());
   
   gameUuid_ = std::move(uuid);
}

ByteArray CMSGJoinGame::serialize() const
{
  return ByteArray(0);
}