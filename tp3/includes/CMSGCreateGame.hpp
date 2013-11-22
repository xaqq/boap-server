#pragma once

#include <string>  
#include "APacket.hpp"
#include "ByteArray.hpp"

class APacketHandler;

/**
 *  Packet sent by client when they want to create a new game
 */
class CMSGCreateGame : public APacket
{
public:
  CMSGCreateGame(std::shared_ptr<AClient> source);
  CMSGCreateGame(const CMSGCreateGame& orig);
  virtual ~CMSGCreateGame();
  
   /**
   * This function MUST be implemented in all APacket's subclasses; This is
   * required because this allows for double dispatch to happen.
   * 
   * 
   * @param handler
   */
  virtual bool acceptHandler(APacketHandler *handler);
  
  /**
   * Binary layout: gameName
   * @param data
   */
  virtual void unserialize(ByteArray data) override;;
  virtual ByteArray serialize() const;

public:
  std::string gameName_;
};