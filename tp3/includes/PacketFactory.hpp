/* 
 * File:   PacketFactory.hpp
 * Author: xaqq
 *
 * Created on November 5, 2013, 10:42 AM
 */

#ifndef PACKETFACTORY_HPP
#define	PACKETFACTORY_HPP

#include <memory>
#include "ByteArray.hpp"

class APacket;
class AClient;
class PacketFactory
{
public:
  PacketFactory();
  PacketFactory(const PacketFactory& orig) = delete;
  virtual ~PacketFactory();

  static std::shared_ptr<APacket> buildPacket(std::shared_ptr<AClient> source,
                                              std::size_t opcode, ByteArray && data);

private:
};

#endif	/* PACKETFACTORY_HPP */

