/* 
 * File:   HelloPacketHandler.hpp
 * Author: xaqq
 *
 * Created on November 4, 2013, 8:44 PM
 */

#ifndef HELLOPACKETHANDLER_HPP
#define	HELLOPACKETHANDLER_HPP


#include "packets/HelloPacket.hpp"

class HelloPacketHandler : public APacketHandler
{
public:
  HelloPacketHandler();
  HelloPacketHandler(const HelloPacketHandler& orig) = delete;
  virtual ~HelloPacketHandler();

  virtual bool handle(HelloPacket *p);
  virtual bool handle(APacket *p);
private:


};

#endif	/* HELLOPACKETHANDLER_HPP */

