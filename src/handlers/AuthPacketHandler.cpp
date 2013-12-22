/* 
 * File:   HelloPacketHandler.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 8:44 PM
 */

#include "handlers/AuthPacketHandler.hpp"
#include "Log.hpp"
#include "Server.hpp"
#include "packets/CMSGAuthPacket.hpp"
#include "AuthTask.hpp"
#include "Scheduler.hpp"
#include "ATask.hpp"

AuthPacketHandler::AuthPacketHandler() { }

AuthPacketHandler::~AuthPacketHandler() { }

bool AuthPacketHandler::handle(CMSGAuthPacket *p)
{
  
  auto task = std::make_shared<AuthTask>(*p);
 // Scheduler::instance()->runInServerThread(std::bind(&AuthTask::operator (), task));
 
  
  task->schedule(ATask::Thread::MAIN);
  
  return true;
}
