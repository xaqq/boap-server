#include "net/TcpSession.hpp"
#include "net/DefaultTcpProtocolHandler.hpp"
#include <iostream>
#include "Log.hpp"

using namespace Net;

void DefaultTcpProtocolHandler::start()
{
  INFO("Starting default protocol handler on socket."
       "I will act a as non-performant, byte per byte echo protocol");
  session_.request(1);
}

void DefaultTcpProtocolHandler::stop()
{
  INFO("Protocol handler stopped");
}

void DefaultTcpProtocolHandler::bytesAvailable(ByteArray && bytes)
{
  session_.post(std::move(bytes));
  session_.request(1);
}

TcpSession & DefaultTcpProtocolHandler::session()
{
  return session_;
}

const TcpSession & DefaultTcpProtocolHandler::session() const
{
  return session_;
}