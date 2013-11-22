/* 
 * File:   HelloPacketHandler.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 8:44 PM
 */

#include "handlers/HelloPacketHandler.hpp"
#include "packets/HelloPacket.hpp"
#include "Log.hpp"
#include "Client.hpp"
#include "Server.hpp"

HelloPacketHandler::HelloPacketHandler() { }

HelloPacketHandler::~HelloPacketHandler() { }

bool HelloPacketHandler::handle(HelloPacket *p)
{
//  /* Push a MOTD packet to the client who sent this */
//  MotdPacket *packet = new MotdPacket(nullptr);
//  packet->motd_ = "Hey coucou! Beau Message du jour pour toi; Coder en dur.\n";
//  
//  std::shared_ptr<APacket> ptr(packet);
//  
//  p->source()->pushPacket(ptr);
//  Server::instance().world().spawn();
  return true;
}

bool HelloPacketHandler::handle(APacket *)
{
//  INFO("Handling APacket from HelloPacketHandler");
  return true;
}