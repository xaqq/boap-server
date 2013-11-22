#pragma once

#include "handlers/APacketHandler.hpp"
#include "packets/CMSGCreateGame.hpp"

class CreateGameHandler : public APacketHandler
{
public:
  CreateGameHandler();
  CreateGameHandler(const CreateGameHandler& orig) = delete;
  virtual ~CreateGameHandler();
  
  bool handle(CMSGCreateGame *p) override;
private:

};

