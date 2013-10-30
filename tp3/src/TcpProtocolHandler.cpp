#include "net/TcpSession.hpp"
#include "TcpProtocolHandler.hpp"
#include <iostream>
#include "Log.hpp"

using namespace Net;

TcpProtocolHandler::TcpProtocolHandler(TcpSession & s) :
DefaultTcpProtocolHandler(s),
bytesReceived_(0) { }

void TcpProtocolHandler::start()
{
  INFO("Starting TP3 protocol handler !");
  session().request(1);
}

void TcpProtocolHandler::stop()
{
  INFO("Protocol handler stopped");
}

void TcpProtocolHandler::bytesAvailable(ByteArray && bytes)
{
  bytesReceived_ += bytes.size();
  ByteArray msg;
  std::stringstream ss;
  ss << "We received " << bytesReceived_ << " bytes from you." << std::endl;  
  msg.resize(ss.str().size());
  memcpy(&msg[0], ss.str().c_str(), ss.str().size());
  session().post(std::move(msg));
  session().request(1);
}