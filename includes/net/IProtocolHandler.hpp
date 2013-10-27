#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include "ByteArray.hpp"

namespace Net
{
  using boost::asio::ip::tcp;

  class TcpSession;

  class IProtocolHandler
  {
  public:

    IProtocolHandler(TcpSession &);

    virtual ~IProtocolHandler();
    /**
     * This method is called by the socket when the data you requested are available;
     * You SHOULD call session_.request(std::size_t) to request more data, otherwise
     * the connection will be closed;
     * 
     * @param bytes ByteArray you requested; Those data are your responsability now;
     */
    virtual void bytesAvailable(ByteArray &&bytes) = 0;
    virtual void start() = 0;
  };
};