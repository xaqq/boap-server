/* 
 * File:   DefaultUdpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 29, 2013, 10:19 PM
 */

#include "net/DefaultUdpProtocolHandler.hpp"
#include "net/UdpServer.hpp"
#include "Log.hpp"

using namespace Net;

DefaultUdpProtocolHandler::DefaultUdpProtocolHandler(UdpServer &s, boost::asio::ip::udp::endpoint e) : AUdpProtocolHandler(s, e)
{
  INFO("Instanciating DefaultUdpProtocolHandler; I'm an echo server too !");
}

DefaultUdpProtocolHandler::~DefaultUdpProtocolHandler() { }

void DefaultUdpProtocolHandler::bytesAvailable(ByteArray && bytes)
{
  INFO("Received UDP datagram from " << endpoint().address().to_string() << ":" << endpoint().port());
  write(std::move(bytes));
}
