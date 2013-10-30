/* 
 * File:   ATcpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 30, 2013, 1:42 AM
 */

#ifndef ATCPPROTOCOLHANDLER_HPP
#define	ATCPPROTOCOLHANDLER_HPP

#include "net/ITcpProtocolHandler.hpp"
#include "net/TcpSession.hpp"
namespace Net
{

  class ATcpProtocolHandler : public ITcpProtocolHandler
  {
  public:
    ATcpProtocolHandler(TcpSession &session);
    ATcpProtocolHandler(const ATcpProtocolHandler& orig) = delete;
    virtual ~ATcpProtocolHandler();

    virtual void bytesAvailable(ByteArray && bytes) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    /**
     * ProtocolHandler must provide a way to retrieve session.
     * This will be implemented in the TcpDefaultProtocolHandler.
     */
  protected:
    virtual TcpSession &session() final;
    virtual const TcpSession &session() const final;

  private:
    TcpSession &session_;
  };
}
#endif	/* ATCPPROTOCOLHANDLER_HPP */

