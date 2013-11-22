#include "handlers/GameListHandler.hpp"
#include "packets/CMSGGameList.hpp"
#include "packets/SMSGGameList.hpp"
#include "Server.hpp"
#include "world/Game.hpp"
#include "Log.hpp"
#include "AClient.hpp"

GameListHandler::GameListHandler() { }

GameListHandler::~GameListHandler() { }

bool GameListHandler::handle(CMSGGameList *p)
{
  if (!p->source())
    return true;
  
  std::shared_ptr<SMSGGameList> response (new SMSGGameList(p->source()));
  DEBUG("TPTP");
  for (auto game : Server::instance().games())
    {
      response->games_[game->uuid()] = std::make_pair(game->name(), game->countPlayers());
    }
  p->source()->pushPacket(response);
  return true;
}
