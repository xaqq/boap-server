/* 
 * File:   BoapFactory.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 8:46 PM
 */

#pragma once
#include <list>
#include <memory>
#include <boost/asio.hpp>

class APacketHandler;
class AClient;
namespace Net
{
  class  IUdpProtocolHandler;
  class ATcpProtocolHandler;
  class UdpServer;
};

/**
 * This class implementation IS NOT PRESENT in the boapd;
 * The default implementation of protocolhandler, packets, and this factory are
 * available in the default-impl folder;
 * 
 * When linking boapd with your current code, provide an implementation of BoapFactory
 * as this is used the system to instanciate objects.
 */
class BoapFactory
{
public:
  BoapFactory();
  BoapFactory(const BoapFactory& orig) = delete;
  virtual ~BoapFactory();

  static std::shared_ptr<Net::ATcpProtocolHandler> createTcpProtocolHandler();
  static std::shared_ptr<Net::IUdpProtocolHandler> createUdpProtocolHandler(Net::UdpServer &, boost::asio::ip::udp::endpoint e);
  static std::shared_ptr<AClient> createClient();
  static std::list<std::shared_ptr<APacketHandler >> createPacketHandlers();

private:

};


