/* 
 * File:   Tcp.hpp
 * Author: xaqq
 *
 * Created on November 11, 2013, 2:45 PM
 */

#ifndef TCP_HPP
#define	TCP_HPP

#include <boost/asio.hpp>
#include <functional>
#include <memory>

namespace Net
{
  class ATcpProtocolHandler;
  class AUdpProtocolHandler;
  class UdpServer;
  typedef std::function<std::shared_ptr<ATcpProtocolHandler>()> TcpHandlerFactory;
  typedef std::function<std::shared_ptr<AUdpProtocolHandler>(UdpServer &, boost::asio::ip::udp::endpoint e)> UdpHandlerFactory;
};

#include "TcpServer.hpp"
#include "TcpSession.hpp"
#include "ATcpProtocolHandler.hpp"
#include "AUdpProtocolHandler.hpp"
#include "UdpServer.hpp"


#endif	/* TCP_HPP */

