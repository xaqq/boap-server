#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include "ByteArray.hpp"

#pragma once

class APacket;
namespace Net
{
  using boost::asio::ip::tcp;

  class TcpSession;

  class ITcpProtocolHandler
  {
  public:

    ITcpProtocolHandler(TcpSession &) { };

    virtual ~ITcpProtocolHandler() { };
    /**
     * This method is called by the socket when the data you requested are available;
     * You SHOULD call session_.request(std::size_t) to request more data, otherwise
     * the connection will be closed;
     * 
     * @param bytes ByteArray you requested; Those data are your responsability now;
     */
    virtual void bytesAvailable(ByteArray && bytes) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void pushPacket(std::shared_ptr<APacket> p) = 0;

    virtual void disconnect() = 0;

    /**
     * ProtocolHandler must provide a way to retrieve session.
     * This will be implemented in the TcpDefaultProtocolHandler.
     */
  protected:
    virtual TcpSession &session() = 0;
    virtual const TcpSession &session() const = 0;
  };
};