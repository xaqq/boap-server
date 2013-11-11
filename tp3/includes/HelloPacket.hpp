/* 
 * File:   HelloPacket.hpp
 * Author: xaqq
 *
 * Created on November 4, 2013, 8:45 PM
 */

#ifndef HELLOPACKET_HPP
#define	HELLOPACKET_HPP

#include "APacket.hpp"

class APacketHandler;
class HelloPacket : public APacket
{
public:
  HelloPacket(std::shared_ptr<AClient> source);
  HelloPacket(const HelloPacket& orig) = delete;
  virtual ~HelloPacket();
  
   /**
   * This function MUST be implemented in all APacket's subclasses; This is
   * required because this allows for double dispatch to happen.
   * 
   * 
   * @param handler
   */
  virtual bool acceptHandler(APacketHandler *handler);
  
  virtual void unserialize(ByteArray data) override;;
  virtual ByteArray serialize() const;
  
private:

};

#endif	/* HELLOPACKET_HPP */

