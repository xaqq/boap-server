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
#include "ITcpProtocolHandler.hpp"
#include "IUdpProtocolHandler.hpp"


namespace Net
{

  class UdpServer : public std::enable_shared_from_this<UdpServer>
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
    
    void write(ByteArray &&data, boost::asio::ip::udp::endpoint);

  private:
    void do_write();
    enum
    {
      PACKET_MAX_SIZE = 4096
    };
    bool writing_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remoteEndpoint_;
    ByteArray buffer_;
    std::shared_ptr<IUdpProtocolHandler> protocolHandler_;
    // need thread safe queue
    std::queue<std::pair<boost::asio::ip::udp::endpoint, ByteArray>> packetQueue_;
  };
}

#endif	/* UDPSERVER_HPP */

