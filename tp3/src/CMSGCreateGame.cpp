
#include "CMSGCreateGame.hpp"
#include <assert.h>
#include "Log.hpp"
#include "APacketHandler.hpp"
#include <string>
#include <algorithm>

CMSGCreateGame::CMSGCreateGame(std::shared_ptr<AClient> source) : APacket(source) { }

CMSGCreateGame::CMSGCreateGame(const CMSGCreateGame& orig) : APacket(orig)
{
  gameName_ = orig.gameName_;
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
   std::string name(data.begin(), data.end());
   
   gameName_ = std::move(name);
}

ByteArray CMSGCreateGame::serialize() const
{
  return ByteArray(0);
}