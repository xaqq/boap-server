/* 
 * File:   HelloPacketHandler.cpp
 * Author: xaqq
 * 
 * Created on November 4, 2013, 8:44 PM
 */

#include "HelloPacketHandler.hpp"
#include "HelloPacket.hpp"
#include "Log.hpp"

HelloPacketHandler::HelloPacketHandler() { }

HelloPacketHandler::~HelloPacketHandler() { }

bool HelloPacketHandler::handle(HelloPacket *p)
{
  INFO("Handling HelloPacket from HelloPacketHandler");
}

bool HelloPacketHandler::handle(APacket *p)
{
  INFO("Handling APacket from HelloPacketHandler");
}