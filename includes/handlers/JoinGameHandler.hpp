#pragma once

#include "handlers/APacketHandler.hpp"

/**
 * This is a game packet opcode, which means it runs in the game's thread.
 */
class JoinGameHandler : public APacketHandler
{
public:
  JoinGameHandler();
  JoinGameHandler(const JoinGameHandler& orig) = delete;
  virtual ~JoinGameHandler();
  
  virtual bool handle(class CMSGJoinGame *p);
  
private:


};