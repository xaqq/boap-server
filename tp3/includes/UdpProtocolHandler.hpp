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
    UdpProtocolHandler(UdpServer &);
    virtual ~UdpProtocolHandler();

    virtual void bytesAvailable(ByteArray && bytes, boost::asio::ip::udp::endpoint e);

  private:
    std::map<boost::asio::ip::udp::endpoint, std::function<void (ByteArray &&)>> handlers_;
  };
}
#endif	/* UDPPROTOCOLHANDLER_HPP */

