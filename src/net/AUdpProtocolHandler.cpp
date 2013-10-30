/* 
 * File:   AUdpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 30, 2013, 3:44 AM
 */

#include "net/AUdpProtocolHandler.hpp"
#include "net/UdpServer.hpp"
using namespace Net;

AUdpProtocolHandler::AUdpProtocolHandler(UdpServer &s) : IUdpProtocolHandler(s),
server_(s) { }

AUdpProtocolHandler::~AUdpProtocolHandler() { }

void AUdpProtocolHandler::write(ByteArray && bytes, boost::asio::ip::udp::endpoint e)
{
  server_.write(std::move(bytes), e);
}