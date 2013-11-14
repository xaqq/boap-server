/* 
 * File:   HelloPacketHandler.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 8:44 PM
 */

#include "AuthPacketHandler.hpp"
#include "HelloPacket.hpp"
#include "Log.hpp"
#include "Client.hpp"
#include "MotdPacket.hpp"
#include "Server.hpp"
#include "CMSGAuthPacket.hpp"
#include "AuthTask.hpp"
#include "Scheduler.hpp"

AuthPacketHandler::AuthPacketHandler() { }

AuthPacketHandler::~AuthPacketHandler() { }

bool AuthPacketHandler::handle(CMSGAuthPacket *p)
{
  INFO("Handling auth");
  
  auto lama = std::make_shared<AuthTask>();
  Scheduler::instance()->runInServerThread(std::bind(&AuthTask::operator (), lama));
  
  return true;
}
