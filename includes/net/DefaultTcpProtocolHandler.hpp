#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include "net/ITcpProtocolHandler.hpp"
#include "TcpSession.hpp"

namespace Net
{
  using boost::asio::ip::tcp;

  class TcpSession;

  class DefaultTcpProtocolHandler : public ITcpProtocolHandler
  {
  public:

    DefaultTcpProtocolHandler(TcpSession & s) : ITcpProtocolHandler(s), session_(s) { }
    virtual ~DefaultTcpProtocolHandler() { };

    void bytesAvailable(ByteArray && bytes);
    void start();
    void stop();

  private:
    TcpSession &session_;
   
  protected:

    TcpSession &session() override;
    const TcpSession &session() const override;
  };
};

