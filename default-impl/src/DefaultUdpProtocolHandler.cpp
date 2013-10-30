/* 
 * File:   DefaultUdpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 29, 2013, 10:19 PM
 */

#include "net/DefaultUdpProtocolHandler.hpp"
#include "Log.hpp"

using namespace Net;

DefaultUdpProtocolHandler::DefaultUdpProtocolHandler() { }

DefaultUdpProtocolHandler::~DefaultUdpProtocolHandler() { }

void DefaultUdpProtocolHandler::bytesAvailable(ByteArray && bytes,
                                               std::pair<unsigned short, std::string> endpoint)
{
  INFO("Received UDP datagram from " << endpoint.second << ":" << endpoint.first);
}