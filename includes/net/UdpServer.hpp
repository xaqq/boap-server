/* 
 * File:   UdpServer.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 7:40 PM
 */

#ifndef UDPSERVER_HPP
#define	UDPSERVER_HPP
#include <boost/asio.hpp>
#include <queue>
#include <memory>
#include "AUdpProtocolHandler.hpp"
#include "ByteArray.hpp"
#include "SafeQueue.hpp"
#include "Network.hpp"

namespace Net
{

  class UdpServer : public std::enable_shared_from_this<UdpServer>
  {
  public:

    UdpServer(boost::asio::io_service& io_service, short port, UdpHandlerFactory factory);
    UdpServer(const UdpServer& orig) = delete;
    virtual ~UdpServer();
    /**
     * Called by signal handler when receiving SIGINT
     */
    void stop();

    /**
     * Schedule read on socket
     */
    void start_receive();

    void write(ByteArray data, boost::asio::ip::udp::endpoint);

    boost::asio::io_service &ioService();
  private:
    std::map<boost::asio::ip::udp::endpoint, std::shared_ptr<AUdpProtocolHandler >> handlers_;

    /**
     * Cleanup handler for inactive endpoint;
     */
    void cleanup();

    void do_write();

    enum
    {
      PACKET_MAX_SIZE = 4096,
      INACTIVE_DELAY = 10
    };

    /**
     * Boolean flag for the server to know wether or not it is writing.
     */
    bool writing_;

    /**
     * The boost socket
     */
    boost::asio::ip::udp::socket socket_;

    /**
     * The boost endpoint
     */
    boost::asio::ip::udp::endpoint remoteEndpoint_;

    /**
     * The read buffer
     */
    ByteArray buffer_;

    /**
     * The outgoing packet queue
     */
    SafeQueue<std::pair<boost::asio::ip::udp::endpoint, ByteArray >> packetQueue_;

    /**
     * Timer to call the cleanup method
     */
    boost::asio::deadline_timer cleanupTimer_;

    /**
     * Functor to create a new protocol handler
     */
    UdpHandlerFactory handlerFactory_;

  };
}

#endif	/* UDPSERVER_HPP */

