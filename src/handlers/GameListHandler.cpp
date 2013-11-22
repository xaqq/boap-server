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
  for (auto game : Server::instance().games())
    {
      SMSGGameListData::GameListEntry *entry = response->data_.add_entry();
      entry->set_countplayers(game->countPlayers());
      entry->set_uuid(game->uuid());
      entry->set_gamename(game->name());
    }
  p->source()->pushPacket(response);
  return true;
}
