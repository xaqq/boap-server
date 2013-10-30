/* 
 * File:   UdpProtocolHandler.cpp
 * Author: xaqq
 * 
 * Created on October 30, 2013, 1:33 AM
 */

#include "UdpProtocolHandler.hpp"
#include "Log.hpp"
using namespace Net;

UdpProtocolHandler::UdpProtocolHandler(UdpServer &s) : AUdpProtocolHandler(s) { }

UdpProtocolHandler::~UdpProtocolHandler() { }

void UdpProtocolHandler::bytesAvailable(ByteArray && bytes, boost::asio::ip::udp::endpoint e)
{
  if (handlers_.count(e))
    {
      handlers_[e](std::move(bytes));
    }
  else
    {
      std::stringstream s;
      for (auto c : bytes)
        s << c;
      INFO("Unkown endpoint; AuthChain is '" << s.str() << "' ;");
    }
}