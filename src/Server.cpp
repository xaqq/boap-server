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

Server::Server() : isRunning_(true) { }

Server::~Server() { }

void Server::flush_operations()
{
  std::function<void () > f;

  while (operationQueue_.tryPop(f))
    {
      f();
    }
}

void Server::run()
{
  while (isRunning_)
    {
      INFO("Server is running. Stats: " << clients_.size() << " clients.");
      flush_operations();
      sleep(3);
    }
}

void Server::addClient(std::shared_ptr<AClient> c)
{
  INFO("scheduling client add to server;");

  Scheduler::instance()->runInServerThread(std::bind(
                                                     static_cast<void (ClientList::*)(const std::shared_ptr<AClient> &)> (&std::list < std::shared_ptr < AClient >> ::push_back)
                                                     , &clients_, c));
}

void Server::stop()
{
  INFO("Stopping server");
  isRunning_ = false;
}