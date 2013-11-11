#include "net/TcpSession.hpp"
#include <iostream>
#include <functional>
#include "Log.hpp"
#include "BoapFactory.hpp"
#include "net/ATcpProtocolHandler.hpp"

using namespace Net;

TcpSession::TcpSession(tcp::socket socket) :
socket_(std::move(socket)),
protocolHandler_(BoapFactory::createTcpProtocolHandler()),
writing_(false),
reading_(false),
stopping_(false)
{
  INFO("New TcpSession created:" << this);
}

TcpSession::~TcpSession()
{
  INFO("TcpSession destroyed");
  socket_.close();
}

void TcpSession::request(std::size_t length)
{
  readBuffers_.push(std::move(ByteArray(length)));
  do_read();
}

void TcpSession::do_read()
{
  if (reading_ || readBuffers_.empty() || stopping_)
    return;
  reading_ = true;
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
                          this->stopped();
      }
  });
}

bool TcpSession::post(ByteArray && bytes)
{
  if (stopping_)
    {
      DEBUG("Session is stopping so post() rejected the packet");
      return false;
    }
  packetQueue_.push(std::move(bytes));
  socket_.get_io_service().post(std::bind(&TcpSession::do_write, shared_from_this()));
  return true;
}

void TcpSession::do_write()
{
  if (writing_ || packetQueue_.empty())
    return;
  writing_ = true;
  auto self(shared_from_this());
  auto bytePtr = std::make_shared<ByteArray > (std::move(packetQueue_.pop()));

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
                           this->stopped();
      }
  });

}

void TcpSession::start()
{
  INFO("Starting TcpSession: " << this);
  protocolHandler_->setSession(shared_from_this());
  protocolHandler_->start();
}

void TcpSession::stopped()
{
  DEBUG("TcpSession stopped: " << this);
  protocolHandler_->disconnected();
}

void TcpSession::stop(bool graceful /* = true */)
{
  if (!graceful)
    {
      socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
      socket_.close();
    }
  else
    {
      socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_receive);
      stopping_ = true;
    }
}