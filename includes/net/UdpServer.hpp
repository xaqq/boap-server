/* 
 * File:   UdpServer.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 7:40 PM
 */

#ifndef UDPSERVER_HPP
#define	UDPSERVER_HPP
#include <boost/asio.hpp>

#include "ITcpProtocolHandler.hpp"


namespace Net
{

  class UdpServer
  {
  public:

    UdpServer(boost::asio::io_service& io_service, short port);
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

  private:
    enum
    {
      PACKET_MAX_SIZE = 4096
    };
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remoteEndpoint_;
    ByteArray buffer_;
  };
}

#endif	/* UDPSERVER_HPP */

