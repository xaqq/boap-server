/* 
 * File:   APacketHandler.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 8:19 PM
 */

#include "handlers/APacketHandler.hpp"
#include "Log.hpp"

APacketHandler::APacketHandler() { }

APacketHandler::~APacketHandler() { }

bool APacketHandler::handle(APacket *p)
{
  return true;
}