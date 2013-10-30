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
    void bytesAvailable(ByteArray &&bytes);
    void start();
    void stop();

  private:
    void recvHeader(const char *data, std::size_t length);
    void recvBody(const char *data, std::size_t length);

    TcpSession &session_;
    short packetSize_;
    short opcode_;

    enum
    {
      PACKET_HEADER = 4
    };

    enum State
    {
      IDLE, WAIT_HEADER, WAIT_BODY
    };
    enum State state_;

  };
};

