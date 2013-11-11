/* 
 * File:   AdminTcpHandler.hpp
 * Author: xaqq
 *
 * Created on November 11, 2013, 2:29 PM
 */

#ifndef ADMINTCPHANDLER_HPP
#define	ADMINTCPHANDLER_HPP

#include "net/ATcpProtocolHandler.hpp"

namespace Net
{

  class AdminTcpHandler : public ATcpProtocolHandler
  {
  public:
    AdminTcpHandler();
    AdminTcpHandler(const AdminTcpHandler& orig);
    virtual ~AdminTcpHandler();
    
    virtual void bytesAvailable(ByteArray &&bytes) override;
  private:

  };
};
#endif	/* ADMINTCPHANDLER_HPP */

