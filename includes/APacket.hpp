/* 
 * File:   APacket.hpp
 * Author: xaqq
 *
 * Created on November 4, 2013, 7:10 PM
 */
#pragma once

#include <memory>
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
  
protected:  
  std::shared_ptr<AClient> source_;

};
