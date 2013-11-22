/* 
 * File:   APacketHandler.hpp
 * Author: xaqq
 *
 * Created on November 4, 2013, 8:19 PM
 */

#ifndef APACKETHANDLER_HPP
#define	APACKETHANDLER_HPP

class APacket;
class HelloPacket;
class UdpAuthPacket;
class CMSGAuthPacket;

class APacketHandler
{
public:
  APacketHandler();
  APacketHandler(const APacketHandler& orig) = delete;
  virtual ~APacketHandler();


  virtual bool handle(APacket *p);

  virtual bool handle(HelloPacket *)
  {
    return true;
  }

  virtual bool handle(UdpAuthPacket *)
  {
    return true;
  }

  virtual bool handle(CMSGAuthPacket *)
  {
    return true;
  }

  virtual bool handle(class CMSGCreateGame *)
  {
    return true;
  }

private:

};

#endif	/* APACKETHANDLER_HPP */

