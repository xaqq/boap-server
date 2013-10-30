/* 
 * File:   AUdpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 30, 2013, 3:44 AM
 */

#ifndef AUDPPROTOCOLHANDLER_HPP
#define	AUDPPROTOCOLHANDLER_HPP

#include "IUdpProtocolHandler.hpp"

namespace Net
{
  class UdpServer;

  class AUdpProtocolHandler : public IUdpProtocolHandler
  {
  public:
    AUdpProtocolHandler(UdpServer &s);
    AUdpProtocolHandler(const AUdpProtocolHandler& orig) = delete;
    virtual ~AUdpProtocolHandler();
  protected:
    /**
     * Call this function to write data to a endpoint; ByteArray will be passed
     * to the UDP server;
     */
    virtual void write(ByteArray && bytes, boost::asio::ip::udp::endpoint e) final;
    UdpServer &server_;

  };
}
#endif	/* AUDPPROTOCOLHANDLER_HPP */

