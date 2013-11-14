#pragma once

#include <string>  
#include "APacket.hpp"
#include "ByteArray.hpp"

class APacketHandler;
class CMSGAuthPacket : public APacket
{
public:
  CMSGAuthPacket(std::shared_ptr<AClient> source);
  CMSGAuthPacket(const CMSGAuthPacket& orig) = delete;
  virtual ~CMSGAuthPacket();
  
   /**
   * This function MUST be implemented in all APacket's subclasses; This is
   * required because this allows for double dispatch to happen.
   * 
   * 
   * @param handler
   */
  virtual bool acceptHandler(APacketHandler *handler);
  
  /**
   * Binary layout: username\0password
   * @param data
   */
  virtual void unserialize(ByteArray data) override;;
  virtual ByteArray serialize() const;

private:
  std::string username_;
  std::string password_;
};