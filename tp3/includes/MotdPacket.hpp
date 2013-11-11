/* 
 * File:   MotdPacket.hpp
 * Author: xaqq
 *
 * Created on November 7, 2013, 12:05 AM
 */

#ifndef MOTDPACKET_HPP
#define	MOTDPACKET_HPP

#include "APacket.hpp"

class APacketHandler;
class MotdPacket : public APacket
{
public:
  MotdPacket(std::shared_ptr<AClient> source);
  MotdPacket(const MotdPacket& orig) = delete;
  virtual ~MotdPacket();
  
   /**
   * This function MUST be implemented in all APacket's subclasses; This is
   * required because this allows for double dispatch to happen.
   * 
   * 
   * @param handler
   */
  virtual bool acceptHandler(APacketHandler *handler);
  
  virtual void unserialize(ByteArray &&data);
  virtual ByteArray serialize() const;


  std::string motd_;
  
};

#endif	/* MOTDPACKET_HPP */

