/* 
 * File:   DefaultUdpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 10:19 PM
 */

#ifndef DEFAULTUDPPROTOCOLHANDLER_HPP
#define	DEFAULTUDPPROTOCOLHANDLER_HPP

#include <string>
#include "net/IUdpProtocolHandler.hpp"

namespace Net
{
  class UdpServer;

  class DefaultUdpProtocolHandler : public IUdpProtocolHandler
  {
  public:
    DefaultUdpProtocolHandler(UdpServer &s);
    DefaultUdpProtocolHandler(const DefaultUdpProtocolHandler& orig) = delete;
    virtual ~DefaultUdpProtocolHandler();

    virtual void bytesAvailable(ByteArray && bytes, boost::asio::ip::udp::endpoint e);
  protected:
    /**
     * Call this function to write data to a endpoint; ByteArray will be passed
     * to the UDP server;
     */
    void write(ByteArray && bytes, boost::asio::ip::udp::endpoint e);
    UdpServer &server_;
  };

}
#endif	/* DEFAULTUDPPROTOCOLHANDLER_HPP */

