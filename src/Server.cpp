/* 
 * File:   Server.cpp
 * Author: xaqq
 * 
 * Created on October 29, 2013, 6:24 PM
 */

#include <unistd.h>

#include "Server.hpp"
#include "Log.hpp"
#include "AClient.hpp"
#include "BoapFactory.hpp"
#include "Scheduler.hpp"
#include "APacket.hpp"


Server *Server::instance_ = nullptr;

Server &Server::instance()
{
  if (!instance_)
    instance_ = new Server();
  return *instance_;
}

Server::Server() : isRunning_(true),
packetHandlers_(BoapFactory::createPacketHandlers()) { }

Server::~Server() { }

void Server::flush_operations()
{
  std::function<void () > f;

  while (operationQueue_.tryPop(f))
    {
      f();
    }
}

void Server::handle_packets()
{
  std::shared_ptr<APacket> packet;

  while (packets_.tryPop(packet))
    {
      DEBUG("FOUND PACKET");
      for (auto handler : packetHandlers_)
        {
          packet->acceptHandler(handler.get());
        }
    }
}

void Server::run()
{
  while (isRunning_)
    {
      INFO("Server is running. Stats: " << clients_.size() << " clients.");
      flush_operations();
      handle_packets();
      sleep(3);
    }
}

void Server::addClient(std::shared_ptr<AClient> c)
{
  INFO("scheduling client add to server;");

  Scheduler::instance()->runInServerThread(std::bind(
                                                     static_cast<void (ClientList::*)(const std::shared_ptr<AClient> &)> (&ClientList::push_back)
                                                     , &clients_, c));
}

void Server::removeClient(std::shared_ptr<AClient> c)
{
  INFO("scheduling client removal from server;");

  Scheduler::instance()->runInServerThread(std::bind(&ClientList::remove
                                                     , &clients_, c));
}

void Server::stop()
{
  INFO("Stopping server");
  isRunning_ = false;
}