/* 
 * File:   UdpServer.cpp
 * Author: xaqq
 * 
 * Created on October 29, 2013, 7:40 PM
 */
#include <memory>
#include "net/UdpServer.hpp"
#include "Log.hpp"
#include "BoapFactory.hpp"
using namespace Net;
using namespace boost::asio::ip;

UdpServer::UdpServer(boost::asio::io_service& io_service, short port) :
socket_(io_service, udp::endpoint(udp::v4(), port)),
buffer_(PACKET_MAX_SIZE),
writing_(false),
cleanupTimer_(io_service, boost::posix_time::seconds(10))
{
  start_receive();
  cleanupTimer_.async_wait(std::bind(&UdpServer::cleanup, this));
}

UdpServer::~UdpServer()
{
  INFO("UdpServer deleted");
}

void UdpServer::stop()
{
  INFO("Stopping UDP server...");
  socket_.get_io_service().stop();
}

void UdpServer::start_receive()
{

  socket_.async_receive_from(
                             boost::asio::buffer(buffer_), remoteEndpoint_,
                             [this](boost::system::error_code ec,
                                    std::size_t bytes)
  {

                             if (!handlers_.count(remoteEndpoint_))
      {
                             INFO("Unkown UDP endpoint; Will instanciate protocol handler");
                             handlers_[remoteEndpoint_] = BoapFactory::createUdpProtocolHandler(*this, remoteEndpoint_);
      }
                             handlers_[remoteEndpoint_]->bytesAvailable(std::move(buffer_));
                             handlers_[remoteEndpoint_]->lastActivity(time(NULL));
                             buffer_.resize(PACKET_MAX_SIZE);
                             start_receive();
  });
}

void UdpServer::cleanup()
{
  cleanupTimer_.expires_at(cleanupTimer_.expires_at() + boost::posix_time::seconds(10));
  cleanupTimer_.async_wait(std::bind(&UdpServer::cleanup, this));
  for (auto it = handlers_.begin(); it != handlers_.end();
          )
    {
      if (time(NULL) - (*it).second->lastActivity() > INACTIVE_DELAY)
        {
          INFO("Removing inactive handler...");
          it = handlers_.erase(it);
        }
      else
        {
          ++it;
        }
    }
}

void UdpServer::write(ByteArray && data, boost::asio::ip::udp::endpoint e)
{
  packetQueue_.push(std::make_pair(e, std::move(data)));
  socket_.get_io_service().post(std::bind(&UdpServer::do_write, this));
}

void UdpServer::do_write()
{
  if (writing_ || packetQueue_.empty())
    return;
  writing_ = true;
  auto bytePtr = std::make_shared<ByteArray > (std::move(packetQueue_.front().second));
  boost::asio::ip::udp::endpoint e = packetQueue_.front().first;
  packetQueue_.pop();

  socket_.async_send_to(boost::asio::buffer(*bytePtr), e,
                        [this, bytePtr, e](boost::system::error_code ec, std::size_t)
  {
                        writing_ = false;
                        if (!ec)
      {
                        do_write();
      }
    else
      {
                        ERROR("Error writing to UDP endpoint " << e.address().to_string() << ec);
      }
  });
}

boost::asio::io_service &UdpServer::ioService()
{
  return socket_.get_io_service();
}
