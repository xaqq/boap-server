/* 
 * File:   JoinGameHandler.cpp
 * Author: xaqq
 * 
 * Created on November 24, 2013, 12:30 AM
 */

#include "Log.hpp"
#include "handlers/JoinGameHandler.hpp"
#include "packets/CMSGJoinGame.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "world/Game.hpp"

JoinGameHandler::JoinGameHandler() { }

JoinGameHandler::~JoinGameHandler() { }

bool JoinGameHandler::handle(CMSGJoinGame* p)
{
  std::shared_ptr<Client> client = std::dynamic_pointer_cast<Client > (p->source());
  bool ok = false;

  if (!client || !client->authenticated())
    {
      INFO("Client trying to join but not existing or not auth");
      return true;
    }
  for (auto game : Server::instance().games())
    {
      if (game->uuid() == p->data_.gameuuid())
        {
          DEBUG("found game ... todo join");
          ok = game->joinGame(client);
//          game->registerObserver(client);
          if (ok)
            {
              
            }
        }
    }

}
