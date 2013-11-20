/* 
 * File:   APacket.hpp
 * Author: xaqq
 *
 * Created on November 4, 2013, 7:10 PM
 */
#pragma once

#include <memory>
#include "ByteArray.hpp"
class AClient;
class APacketHandler;
class APacket
{
public:
  APacket(std::shared_ptr<AClient> source);
  APacket(const APacket& orig);
  virtual ~APacket();
  
  std::shared_ptr<AClient> source();
  
  /**
   * This function MUST be implemented in all APacket's subclasses; This is
   * required because this allows for double dispatch to happen.
   * 
   * 
   * @param handler
   */
  virtual bool acceptHandler(APacketHandler *handler);

  virtual void unserialize(ByteArray data) = 0;
  virtual ByteArray serialize() const = 0 ;
  
  enum {
                        CMSG_HELLO      = 0x0001,
                        CMSG_AUTH       = 0x0002,
                        SMSG_MOTD       =  0x1001,
                        SMSG_UDP_CODE = 0x1002
                                
 };
  
protected:  
  std::shared_ptr<AClient> source_;

};
