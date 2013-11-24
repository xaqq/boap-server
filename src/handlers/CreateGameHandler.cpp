/* 
 * File:   CreateGameHandler.cpp
 * Author: xaqq
 * 
 * Created on November 22, 2013, 12:13 AM
 */

#include "Log.hpp"
#include "handlers/CreateGameHandler.hpp"
#include "Server.hpp"
#include "world/Game.hpp"
#include "packets/SMSGCreateGame.hpp"
#include "Client.hpp"
#include "ProtobufDef.hpp"

CreateGameHandler::CreateGameHandler() { }

CreateGameHandler::~CreateGameHandler() { }

bool CreateGameHandler::handle(CMSGCreateGame *p)
{
  auto client = std::dynamic_pointer_cast<Client > (p->source());
  if (!client)
    {
      WARN("NO SOURCE TO CREATE GAME");
      return true;
    }
  auto response = std::make_shared<SMSGCreateGame > (p->source());

  if (!client->authenticated())
    {
      response->data_.set_success(false);
      response->data_.set_errormsg("You are not authenticated so you cannot create a new game.");
      client->pushPacket(response);
      return true;
    }

  if (p->data_.gamename() == "")
    {
      response->data_.set_success(false);
      response->data_.set_errormsg("Name cannot be empty;");
    }

  for (auto game : Server::instance().games())
    {
      if (game->name() == p->data_.gamename())
        {
          WARN("Game with is name already exists, not creating");
          response->data_.set_success(false);
          response->data_.set_errormsg("Name already taken.");
          p->source()->pushPacket(response);
          return true;
        }
    }

  std::string sceneName;
  if (p->data_.has_scenename())
    sceneName = p->data_.scenename();
  else
    sceneName = "Test Level";
  
  std::shared_ptr<Game> g(new Game(sceneName));
  g->name(p->data_.gamename());
  response->data_.set_success(true);
  response->data_.set_gameuuid(g->uuid());
  p->source()->pushPacket(response);
  Server::instance().addGame(g);
  return true;
}