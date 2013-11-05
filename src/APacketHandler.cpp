/* 
 * File:   APacketHandler.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 8:19 PM
 */

#include "APacketHandler.hpp"
#include "Log.hpp"

APacketHandler::APacketHandler() { }

APacketHandler::~APacketHandler() { }

bool APacketHandler::handle(APacket *p)
{
  DEBUG("APacketHandler handling APacket, nothing interesting here");
  return true;
}