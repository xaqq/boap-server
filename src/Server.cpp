/* 
 * File:   Server.cpp
 * Author: xaqq
 * 
 * Created on October 29, 2013, 6:24 PM
 */

#include <unistd.h>

#include "Server.hpp"
#include "Log.hpp"

Server::Server() : isRunning_(true) { }

Server::~Server() { }

void Server::flush_operations()
{
  std::function<void ()> f;
  
  while (operationQueue_.tryPop(f))
    {      
      f();
    }
}

void Server::run()
{
  while (isRunning_)
    {
      INFO("Server is running");
      flush_operations();
      sleep(3);
    }
}

void Server::stop()
{
  INFO("Stopping server");
  isRunning_ = false;
}