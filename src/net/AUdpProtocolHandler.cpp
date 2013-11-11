/* 
 * File:   AUdpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 30, 2013, 3:44 AM
 */

#include "net/AUdpProtocolHandler.hpp"
#include "net/UdpServer.hpp"
using namespace Net;

AUdpProtocolHandler::AUdpProtocolHandler(UdpServer &s, boost::asio::ip::udp::endpoint e) :
endpoint_(e),
server_(s) { }

AUdpProtocolHandler::~AUdpProtocolHandler() { }

void AUdpProtocolHandler::write(ByteArray && bytes)
{
  server_.write(std::move(bytes), endpoint_);
  lastActivity_ = time(NULL);
}

boost::asio::ip::udp::endpoint &AUdpProtocolHandler::endpoint()
{
  return endpoint_;
}

const boost::asio::ip::udp::endpoint &AUdpProtocolHandler::endpoint() const
{
  return endpoint_;
}

time_t AUdpProtocolHandler::lastActivity() const
{
  return lastActivity_;
}

void AUdpProtocolHandler::lastActivity(time_t t)
{
  lastActivity_ = t;
}