#pragma once

#include "handlers/APacketHandler.hpp"

/**
 * This handler dispatch packet to game queue;
 */
class GamePacketHandler : public APacketHandler
{
public:
  GamePacketHandler();
  GamePacketHandler(const GamePacketHandler& orig) = delete;
  virtual ~GamePacketHandler();

  /**
   * Forward the CMSGJoinGame packet to the target game; Or send not found (todo)
   * @param p
   * @return 
   */
  virtual bool handle(class CMSGJoinGame *p);

private:


};
