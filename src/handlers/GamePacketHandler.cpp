#include "handlers/GamePacketHandler.hpp"
#include "packets/CMSGGameList.hpp"
#include "Server.hpp"
#include "world/Game.hpp"
#include "Log.hpp"
#include "AClient.hpp"
#include "Client.hpp"
#include "packets/CMSGJoinGame.hpp"

GamePacketHandler::GamePacketHandler() { }

GamePacketHandler::~GamePacketHandler() { }

bool GamePacketHandler::handle(CMSGJoinGame *p)
{  
  std::shared_ptr<Client> client = std::dynamic_pointer_cast<Client> (p->source());

  if (!client || !client->authenticated())
    {
      WARN("Dont forward packet to game -- wrong client");              
      return true;
    }  
  
  for (auto game : Server::instance().games())
    {
      if (game->uuid() == p->data_.gameuuid())
        {
          game->pushPacket(std::shared_ptr<APacket>(new CMSGJoinGame(*p)));
        }
    }

  
  return true;
}
