/* 
 * File:   UdpAuthHandler.hpp
 * Author: xaqq
 *
 * Created on November 11, 2013, 3:39 PM
 */

#ifndef UDPAUTHHANDLER_HPP
#define	UDPAUTHHANDLER_HPP

#include "handlers/APacketHandler.hpp"
#include "packets/CMSGUdpAuth.hpp"

class UdpAuthHandler : public APacketHandler
{
public:
  UdpAuthHandler();
  UdpAuthHandler(const UdpAuthHandler&) = delete;
  virtual ~UdpAuthHandler();
  
  virtual bool handle(CMSGUdpAuth *p);
private:

};

#endif	/* UDPAUTHHANDLER_HPP */

