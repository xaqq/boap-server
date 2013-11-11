#pragma once


#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include <queue>
#include "SafeQueue.hpp"
#include "ByteArray.hpp"
#include "Network.hpp"

namespace Net
{
  using boost::asio::ip::tcp;
  class ATcpProtocolHandler;

  class TcpSession : public std::enable_shared_from_this<TcpSession>
  {
  public:
    TcpSession(tcp::socket socket, std::shared_ptr<ATcpProtocolHandler> handler);
    ~TcpSession();
    /**
     * Called by the server when ready
     */
    void start();

    /**
     * Stop the session. The session will be deleted automatically, but may stay alive 
     * a bit. Calling write() will after stop() will do nothing.
     * @param graceful if set to true, the session will flush out packet before closing.
     */
    void stop(bool graceful = true);

    /**
     * Called by ProtocolHandler implemented to request some data.
     * When thoses data are available, the socket will notify the ProtocolHandler.
     * 
     * Do not call request() again before bytesAvailable() was call on your protocol handler;
     * 
     * request() IS NOT THREAD SAFE.
     * @param bytes number of bytes you request. if set to 0, will returns as soon as something
     * is available;
     */
    void request(std::size_t bytes);

    /**
     * This method is thread safe;
     * @param b the data
     */
    bool post(ByteArray b);

  private:
    /**
     * Internal method called by handlers (read and write) when someting goes wrong.
     * The session is dead at this point - this method will propagate the info to the handler.
     */
    void stopped();
    void do_read();
    void do_read_some();
    void do_write();
    tcp::socket socket_;


    /**
     * The buffer we are reading into.
     */
    ByteArray readBuffer_;

    std::shared_ptr<ATcpProtocolHandler> protocolHandler_;

    /**
     * The packets waiting to be send.
     */
    SafeQueue<ByteArray> packetQueue_;


    bool writing_;
    bool reading_;

    /***
     * Is the session stopping (graceful stop)
     */
    std::atomic_bool stopping_;
  };
};

