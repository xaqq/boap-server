/* 
 * File:   Server.cpp
 * Author: xaqq
 * 
 * Created on October 29, 2013, 6:24 PM
 */

#include <unistd.h>
#include <thread>
#include "Server.hpp"
#include "Log.hpp"
#include "AClient.hpp"
#include "Clock.hpp"
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
  std::size_t size = operationQueue_.size();
  std::size_t i = 0;

  while (i++ < size && operationQueue_.tryPop(f))
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
          if (!packet)
            {
              WARN("No Packet !");
            }
          if (!packet->acceptHandler(handler.get()))
            {
              INFO("Handler dropped packet");
              break;
            }
        }
    }
}

void Server::run()
{
  int ticks_per_sec = 100;
  int ms_per_tick = 1000 / ticks_per_sec;
  
  while (isRunning_)
    {
      Clock::time_point t;
      t = Clock::now();

      // INFO("Server is running. Stats: " << clients_.size() << " clients.");
      flush_operations();
      handle_packets();
      world_.update();
      Milliseconds diff = std::chrono::duration_cast<Milliseconds > (Clock::now() - t);
      
      if (diff.count() > ms_per_tick)
        {
          WARN("Server can't keep up; this tick took " << diff.count() << " instead of maximum " << ms_per_tick);
        }
      else if (diff.count() < ms_per_tick)
        {
          DEBUG("Sleeping for " << (Milliseconds(ms_per_tick) - diff).count());
          std::this_thread::sleep_for(Milliseconds(ms_per_tick) - diff);
        }
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

const Server::ClientList &Server::clients() const
{
  return clients_;
}

World &Server::world()
{
  return world_;
}

const World &Server::world() const
{
  return world_;
}