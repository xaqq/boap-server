#pragma once

#include <string>
#include "APacket.hpp"
#include "net/AUdpProtocolHandler.hpp"

class APacketHandler;

class CMSGUdpAuth : public APacket
{
public:
  CMSGUdpAuth(std::shared_ptr<AClient> source);
  CMSGUdpAuth(const CMSGUdpAuth& orig) = delete;
  virtual ~CMSGUdpAuth();

  /**
   * This function MUST be implemented in all APacket's subclasses; This is
   * required because this allows for double dispatch to happen.
   * 
   * 
   * @param handler
   */
  virtual bool acceptHandler(APacketHandler *handler);

  virtual void unserialize(ByteArray data);
  virtual ByteArray serialize() const;

  const std::string &authCode() const;
  std::shared_ptr<Net::AUdpProtocolHandler> handler();
  void handler(std::shared_ptr<Net::AUdpProtocolHandler>);

private:
  std::string authCode_;
  /**
   * The handler from which the packet originates
   */
  std::shared_ptr<Net::AUdpProtocolHandler> handler_;

};
