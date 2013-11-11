/* 
 * File:   HelloPacketHandler.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 8:44 PM
 */

#include "HelloPacketHandler.hpp"
#include "HelloPacket.hpp"
#include "Log.hpp"
#include "Client.hpp"
#include "MotdPacket.hpp"

HelloPacketHandler::HelloPacketHandler() { }

HelloPacketHandler::~HelloPacketHandler() { }

bool HelloPacketHandler::handle(HelloPacket *p)
{
  INFO("Handling HelloPacket from HelloPacketHandler");
  /* Push a MOTD packet to the client who sent this */
  MotdPacket *packet = new MotdPacket(nullptr);
  packet->motd_ = "Hey coucou! Beau Message du jour pour toi; Coder en dur.\n";
  
  std::shared_ptr<APacket> ptr(packet);
  
  p->source()->pushPacket(ptr);
  p->source()->pushPacket(ptr);
  p->source()->pushPacket(ptr);
  p->source()->disconnect();
  
  return true;
}

bool HelloPacketHandler::handle(APacket *)
{
  INFO("Handling APacket from HelloPacketHandler");
  return true;
}