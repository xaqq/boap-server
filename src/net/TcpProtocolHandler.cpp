#include <iostream>
#include <functional>

#include "net/TcpSession.hpp"
#include "net/TcpProtocolHandler.hpp"
#include "Log.hpp"
#include "Scheduler.hpp"
#include "BoapFactory.hpp"
#include "Client.hpp"
#include "APacket.hpp"
#include "packets/PacketFactory.hpp"
#include "Server.hpp"

using namespace Net;

TcpProtocolHandler::TcpProtocolHandler() :
bytesReceived_(0) { }

void TcpProtocolHandler::start()
{
  INFO("Starting TP3 protocol handler ! Request an asynchronous client creation;");
  client_ = std::static_pointer_cast<Client > (BoapFactory::createClient());

  client_->tcpHandler(shared_from_this());

  Server::instance().addClient(client_);
  request(sizeof (opcode_));
  handler_ = std::bind(&TcpProtocolHandler::readOpcode, this, std::placeholders::_1);
}

void TcpProtocolHandler::stop()
{
  INFO("Protocol handler stopped");
  Server::instance().removeClient(client_);
}

void TcpProtocolHandler::readOpcode(ByteArray bytes)
{
  assert(bytes.size() == sizeof (opcode_));
  memcpy(&opcode_, &bytes[0], sizeof (opcode_));

  handler_ = std::bind(&TcpProtocolHandler::readSize, this, std::placeholders::_1);
  request(sizeof (packetSize_));
}

void TcpProtocolHandler::readSize(ByteArray bytes)
{
  assert(bytes.size() == sizeof (packetSize_));
  memcpy(&packetSize_, &bytes[0], sizeof (packetSize_));

  if (packetSize_ > 1024)
    {
      WARN("Packet too big ! (" << packetSize_ << ")");
      handler_ = std::bind(&TcpProtocolHandler::readOpcode, this, std::placeholders::_1);
      request(sizeof (opcode_));
      return;
    }

  if (packetSize_ == 0)
    {
      readBody(ByteArray(0));
      return;
    }

  handler_ = std::bind(&TcpProtocolHandler::readBody, this, std::placeholders::_1);
  request(packetSize_);
}

void TcpProtocolHandler::readBody(ByteArray bytes)
{
  assert(bytes.size() == packetSize_);

  std::shared_ptr< APacket > packet = PacketFactory::buildPacket(client_, opcode_, std::move(bytes));
  if (packet)
    Server::instance().pushPacket(packet);


  handler_ = std::bind(&TcpProtocolHandler::readOpcode, this, std::placeholders::_1);
  request(sizeof (opcode_));
}

void TcpProtocolHandler::bytesAvailable(ByteArray bytes)
{
  handler_(std::move(bytes));
}

void TcpProtocolHandler::disconnected()
{
  DEBUG("Custom protocolhandler disconnected, signaling client that it was disconnected.");
  Scheduler::instance()->runInServerThread(std::bind(&AClient::disconnected, client_));
}