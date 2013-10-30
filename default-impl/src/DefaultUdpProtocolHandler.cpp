/* 
 * File:   DefaultUdpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 29, 2013, 10:19 PM
 */

#include "net/DefaultUdpProtocolHandler.hpp"
#include "net/UdpServer.hpp"
#include "Log.hpp"
#include "net/DefaultTcpProtocolHandler.hpp"

using namespace Net;

DefaultUdpProtocolHandler::DefaultUdpProtocolHandler(UdpServer &s) : IUdpProtocolHandler(s),
server_(s)
{
  INFO("Instanciating DefaultUdpProtocolHandler; I'm an echo server too !");
}

DefaultUdpProtocolHandler::~DefaultUdpProtocolHandler() { }

void DefaultUdpProtocolHandler::bytesAvailable(ByteArray && bytes,
                                               boost::asio::ip::udp::endpoint e)
{
  INFO("Received UDP datagram from " << e.address().to_string() << ":" << e.port());
  write(std::move(bytes), e);
}

void DefaultUdpProtocolHandler::write(ByteArray && bytes, boost::asio::ip::udp::endpoint e)
{
  server_.write(std::move(bytes), e);
}