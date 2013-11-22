#pragma once
#include "APacketHandler.hpp"

class GameListHandler : public APacketHandler
{
public:
  GameListHandler();
  GameListHandler(const GameListHandler& orig) = delete;
  virtual ~GameListHandler();
  
  virtual bool handle(class CMSGGameList *p);
  
private:


};