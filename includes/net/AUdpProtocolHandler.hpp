/* 
 * File:   AUdpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 30, 2013, 3:44 AM
 */

#ifndef AUDPPROTOCOLHANDLER_HPP
#define	AUDPPROTOCOLHANDLER_HPP

#include <memory>
#include <boost/asio.hpp>
#include "ByteArray.hpp"

namespace Net
{
  class UdpServer;

  class AUdpProtocolHandler : public std::enable_shared_from_this<AUdpProtocolHandler>
  {
  public:
    AUdpProtocolHandler(UdpServer &s, boost::asio::ip::udp::endpoint e);
    AUdpProtocolHandler(const AUdpProtocolHandler& orig) = delete;
    
    /**
     * The UDP handler is destroyed when it is considered to have timeout.
     */
    virtual ~AUdpProtocolHandler();
    
    virtual void bytesAvailable(ByteArray && bytes) = 0;
    
    virtual boost::asio::ip::udp::endpoint &endpoint();
    virtual const boost::asio::ip::udp::endpoint &endpoint() const;
    
    virtual time_t lastActivity() const;
    virtual void lastActivity(time_t);
  protected:
    /**
     * Call this function to write data to a endpoint; ByteArray will be passed
     * to the UDP server; Helper method
     */
    void write(ByteArray && bytes);
    UdpServer &server_;
    boost::asio::ip::udp::endpoint endpoint_;
    time_t lastActivity_;
  };
}
#endif	/* AUDPPROTOCOLHANDLER_HPP */

