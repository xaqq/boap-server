#include "net/TcpSession.hpp"
#include "net/ProtocolHandler.hpp"
#include <iostream>
#include "Log.hpp"

using namespace Net;

void ProtocolHandler::start()
{
  session_.request(10);
  std::string str("Hello !");
  ByteArray b(str.size());
  memcpy(&b[0], str.c_str(), str.size());
  session_.post(std::move(b));
  state_ = WAIT_HEADER;
}

void ProtocolHandler::stop()
{
  INFO("Protocol handler stopped");
}

void ProtocolHandler::bytesAvailable(ByteArray && bytes)
{
  std::cout << "Read (" << bytes.size() << "): ";
  for (char b : bytes)
    std::cout << b;
  std::cout << std::endl;
  //session_.request(10);
}

void ProtocolHandler::recvHeader(const char *data, std::size_t length)
{
  assert(length == 4);
  memcpy(&packetSize_, &data[0], 2);
  memcpy(&opcode_, &data[2], 2);
  if (packetSize_ > 2048)
    {
      // session_.post("LOL");
    }
  else
    {
      //      session_.do_read(packetSize_);
      state_ = WAIT_BODY;
    }
}

void ProtocolHandler::recvBody(const char *data, std::size_t length)
{
  std::cout << "Packet body" << std::endl;
}
