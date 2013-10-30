#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include "net/ITcpProtocolHandler.hpp"
#include "net/TcpSession.hpp"

#pragma once

namespace Net
{
  using boost::asio::ip::tcp;

  class TcpSession;

  class DefaultTcpProtocolHandler : public ITcpProtocolHandler
  {
  public:

    DefaultTcpProtocolHandler(TcpSession & s) : ITcpProtocolHandler(s), session_(s) { }
    virtual ~DefaultTcpProtocolHandler();

    virtual void bytesAvailable(ByteArray && bytes);
    virtual void start();
    virtual void stop();

  private:
    TcpSession &session_;

  protected:

    TcpSession &session() override;
    const TcpSession &session() const override;
  };
};

