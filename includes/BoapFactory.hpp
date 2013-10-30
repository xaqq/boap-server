/* 
 * File:   BoapFactory.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 8:46 PM
 */

#include "net/ITcpProtocolHandler.hpp"
#include "net/IUdpProtocolHandler.hpp"


#pragma once

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

  static std::shared_ptr<Net::ITcpProtocolHandler> createTcpProtocolHandler(Net::TcpSession &);
  static std::shared_ptr<Net::IUdpProtocolHandler> createUdpProtocolHandler();

private:

};


