#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include "net/ATcpProtocolHandler.hpp"
#include "net/TcpSession.hpp"

#pragma once

namespace Net
{
  using boost::asio::ip::tcp;

  class TcpSession;

  class DefaultTcpProtocolHandler : public ATcpProtocolHandler
  {
  public:

    DefaultTcpProtocolHandler(TcpSession & s) : ATcpProtocolHandler(s) { }
    virtual ~DefaultTcpProtocolHandler();

    virtual void bytesAvailable(ByteArray && bytes);
    virtual void start();
    virtual void stop();
  };
};

