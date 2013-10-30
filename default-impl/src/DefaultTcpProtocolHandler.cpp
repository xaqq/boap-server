#include "net/TcpSession.hpp"
#include "net/DefaultTcpProtocolHandler.hpp"
#include <iostream>
#include "Log.hpp"

using namespace Net;

DefaultTcpProtocolHandler::~DefaultTcpProtocolHandler() { }

void DefaultTcpProtocolHandler::start()
{
  INFO("Starting default protocol handler on socket."
       "I will act a as non-performant, byte per byte echo protocol");
  session().request(1);
}

void DefaultTcpProtocolHandler::stop()
{
  INFO("Protocol handler stopped");
}

void DefaultTcpProtocolHandler::bytesAvailable(ByteArray && bytes)
{
  session().post(std::move(bytes));
  session().request(1);
}
