/* 
 * File:   UdpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 30, 2013, 1:33 AM
 */

#ifndef UDPPROTOCOLHANDLER_HPP
#define	UDPPROTOCOLHANDLER_HPP
#include <map>
#include "net/AUdpProtocolHandler.hpp"
namespace Net
{
  class UdpServer;

  class UdpProtocolHandler : public AUdpProtocolHandler
  {
  public:
    UdpProtocolHandler(UdpServer &, boost::asio::ip::udp::endpoint e);
    virtual ~UdpProtocolHandler();

    virtual void bytesAvailable(ByteArray && bytes);
  };
}
#endif	/* UDPPROTOCOLHANDLER_HPP */

