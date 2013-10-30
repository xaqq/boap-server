/* 
 * File:   DefaultUdpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 10:19 PM
 */

#ifndef DEFAULTUDPPROTOCOLHANDLER_HPP
#define	DEFAULTUDPPROTOCOLHANDLER_HPP

#include <string>
#include "net/IUdpProtocolHandler.hpp"

namespace Net
{

  class DefaultUdpProtocolHandler : public IUdpProtocolHandler
  {
  public:
    DefaultUdpProtocolHandler();
    DefaultUdpProtocolHandler(const DefaultUdpProtocolHandler& orig) = delete;
    virtual ~DefaultUdpProtocolHandler();

    virtual void bytesAvailable(ByteArray && bytes, std::pair<unsigned short, std::string>);
  private:

  };

}
#endif	/* DEFAULTUDPPROTOCOLHANDLER_HPP */

