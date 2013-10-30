#include "net/TcpSession.hpp"
#include "net/ProtocolHandler.hpp"
#include <iostream>
#include <functional>
#include "Log.hpp"

using namespace Net;

TcpSession::TcpSession(tcp::socket socket) :
socket_(std::move(socket)),
protocolHandler_(std::make_shared<ProtocolHandler>(*this)),
writing_(false)
{
  INFO("New TcpSession created:" << this);
}

TcpSession::~TcpSession()
{
  INFO("TcpSession destroyed");
}

void TcpSession::request(std::size_t length)
{
  readBuffers_.push(std::move(ByteArray(length)));
  if (reading_) // queue the buffer;
    {
      return;
    }
  do_read();
}

void TcpSession::do_read()
{
  if (reading_ || readBuffers_.empty())
    return;
  reading_ = true;
  writing_ = true;
  auto self(shared_from_this());
  auto bytePtr = std::make_shared<ByteArray > (std::move(readBuffers_.front()));
  readBuffers_.pop();

  boost::asio::async_read(socket_, boost::asio::buffer(*bytePtr),
                          [this, self, bytePtr]
                          (boost::system::error_code ec, std::size_t length)
  {
                          reading_ = false;
                          if (!ec)
      {
                          protocolHandler_->bytesAvailable(std::move(*bytePtr));
                          do_read();
      }
    else
      {
                          ERROR("Error reading on socket " << ec);
                          this->stop();
      }
  });
}

void TcpSession::post(ByteArray && bytes)
{
  packetQueue_.push(bytes);
  socket_.get_io_service().post(std::bind(&TcpSession::do_write, shared_from_this()));
}

void TcpSession::do_write()
{
  if (writing_ || packetQueue_.empty())
    return;
  writing_ = true;
  auto self(shared_from_this());
  auto bytePtr = std::make_shared<ByteArray > (std::move(packetQueue_.front()));
  packetQueue_.pop();
  // We keep the bytesPtr by value, so we guarantee that the buffer memory stays
  // valid until the read completes.

  boost::asio::async_write(socket_, boost::asio::buffer(*bytePtr),
                           [this, self, bytePtr](boost::system::error_code ec, std::size_t /*length*/)
  {
                           writing_ = false;
                           if (!ec)
      {
                           do_write();
      }
    else
      {
                           ERROR("Error writing on socket " << ec);
                           this->stop();
      }
  });

}

void TcpSession::start()
{
  INFO("Starting TcpSession: " << this);
  protocolHandler_->start();
}

void TcpSession::stop()
{
  INFO("Stopping TcpSession: " << this);
  protocolHandler_->stop();
  socket_.close();
}
