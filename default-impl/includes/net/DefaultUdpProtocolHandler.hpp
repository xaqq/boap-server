/* 
 * File:   DefaultUdpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 10:19 PM
 */

#ifndef DEFAULTUDPPROTOCOLHANDLER_HPP
#define	DEFAULTUDPPROTOCOLHANDLER_HPP

#include <string>
#include "net/AUdpProtocolHandler.hpp"

namespace Net
{
  class UdpServer;

  /**
   * Default UDP Handler; This class receive all datagram the server receive,
   * and send them back; You can build a client-based dispatcher from this class;
   */
  class DefaultUdpProtocolHandler : public AUdpProtocolHandler
  {
  public:
    DefaultUdpProtocolHandler(UdpServer &s);
    DefaultUdpProtocolHandler(const DefaultUdpProtocolHandler& orig) = delete;
    virtual ~DefaultUdpProtocolHandler();

    virtual void bytesAvailable(ByteArray && bytes, boost::asio::ip::udp::endpoint e);
  };

}
#endif	/* DEFAULTUDPPROTOCOLHANDLER_HPP */

