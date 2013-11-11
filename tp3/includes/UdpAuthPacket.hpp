/* 
 * File:   UdpAuthPacket.hpp
 * Author: xaqq
 *
 * Created on November 11, 2013, 3:35 PM
 */

#ifndef UDPAUTHPACKET_HPP
#define	UDPAUTHPACKET_HPP

#include <string>
#include "APacket.hpp"

class APacketHandler;

class UdpAuthPacket : public APacket
{
public:
  UdpAuthPacket(std::shared_ptr<AClient> source);
  UdpAuthPacket(const UdpAuthPacket& orig) = delete;
  virtual ~UdpAuthPacket();

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
  std::shared_ptr<AUdpProtocolHandler> handler();
  void handler(std::shared_ptr<AUdpProtocolHandler>);

private:
  std::string authCode_;
  /**
   * The handler from which the packet originates
   */
  std::shared_ptr<AUdpProtocolHandler> handler;

};

#endif	/* UDPAUTHPACKET_HPP */

