#pragma once

#include <string>  
#include "APacket.hpp"
#include "ByteArray.hpp"
#include "ProtobufDef.hpp"

class APacketHandler;
class CMSGAuthPacket : public APacket
{
public:
  CMSGAuthPacket(std::shared_ptr<AClient> source);
  CMSGAuthPacket(const CMSGAuthPacket& orig);
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

public:
  /**
   * Message data
   */
  CMSGAuthData data_;
};