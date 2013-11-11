/* 
 * File:   UdpAuthHandler.hpp
 * Author: xaqq
 *
 * Created on November 11, 2013, 3:39 PM
 */

#ifndef UDPAUTHHANDLER_HPP
#define	UDPAUTHHANDLER_HPP

#include "APacketHandler.hpp"
#include "UdpAuthPacket.hpp"

class UdpAuthHandler : public APacketHandler
{
public:
  UdpAuthHandler();
  UdpAuthHandler(const UdpAuthHandler& orig);
  virtual ~UdpAuthHandler();
  
  virtual bool handle(UdpAuthPacket *p);
private:

};

#endif	/* UDPAUTHHANDLER_HPP */

