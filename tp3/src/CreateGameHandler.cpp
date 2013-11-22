/* 
 * File:   CreateGameHandler.cpp
 * Author: xaqq
 * 
 * Created on November 22, 2013, 12:13 AM
 */

#include "Log.hpp"
#include "CreateGameHandler.hpp"
#include "Server.hpp"
#include "world/Game.hpp"
#include "SMSGCreateGame.hpp"
#include "AClient.hpp"
#include "Client.hpp"

CreateGameHandler::CreateGameHandler() { }

CreateGameHandler::~CreateGameHandler() { }

bool CreateGameHandler::handle(CMSGCreateGame *p)
{
  auto client = std::dynamic_pointer_cast<Client>(p->source());
  if (!client)
    {
      WARN("NO SOURCE TO CREATE GAME");
      return true;
    }
  auto response = std::make_shared<SMSGCreateGame > (p->source());

  if (!client->authenticated())
    {
      response->success_ = false;
      response->errMsg_ = "You are not authenticated so you cannot create a new game.";
      client->pushPacket(response);
      return true;
    }
  
  for (auto game : Server::instance().games())
    {
      if (game->name() == p->gameName_)
        {
          WARN("Game with is name already exists, not creating");
          response->success_ = false;
          response->errMsg_ = "Name already taken.";
          p->source()->pushPacket(response);
          return true;
        }
    }

  std::shared_ptr<Game> g(new Game());
  g->name(p->gameName_);
  response->success_ = true;
  response->gameUuid_ = g->uuid();
  p->source()->pushPacket(response);
  Server::instance().addGame(g);
  return true;
}