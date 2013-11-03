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

void Server::run()
{
  while (isRunning_)
    {
      INFO("Server is running");
      sleep(3);
    }
}

void Server::stop()
{
  INFO("Stopping server");
  isRunning_ = false;
}