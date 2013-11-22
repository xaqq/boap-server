#pragma once

#include <string>  
#include "APacket.hpp"
#include "ByteArray.hpp"

class APacketHandler;

/**
 *  Packet sent by client when they want to create a new game
 */
class CMSGJoinGame : public APacket
{
public:
  CMSGJoinGame(std::shared_ptr<AClient> source);
  CMSGJoinGame(const CMSGJoinGame& orig);
  virtual ~CMSGJoinGame();
  
   /**
   * This function MUST be implemented in all APacket's subclasses; This is
   * required because this allows for double dispatch to happen.
   * 
   * 
   * @param handler
   */
  virtual bool acceptHandler(APacketHandler *handler);
  
  /**
   * Binary layout: gameUuid
   * @param data
   */
  virtual void unserialize(ByteArray data) override;;
  virtual ByteArray serialize() const;

public:
  std::string gameUuid_;
};