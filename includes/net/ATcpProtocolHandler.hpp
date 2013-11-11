/* 
 * File:   ATcpProtocolHandler.hpp
 * Author: xaqq
 *
 * Created on October 30, 2013, 1:42 AM
 */

#ifndef ATCPPROTOCOLHANDLER_HPP
#define	ATCPPROTOCOLHANDLER_HPP

class APacket;
#include <memory>
#include "ByteArray.hpp"
namespace Net
{
  class TcpSession;

  class ATcpProtocolHandler
  {
  public:
    ATcpProtocolHandler();

    ATcpProtocolHandler(const ATcpProtocolHandler& orig) = delete;
    virtual ~ATcpProtocolHandler();

    virtual void bytesAvailable(ByteArray bytes) = 0;
    virtual bool pushPacket(std::shared_ptr<APacket> p);
    virtual bool write(const std::string &s);

    /**
     * This method is called by the session when it starts.
     * 
     * Protocol handling begins here; You can start requesting data.
     */
    virtual void start() = 0;

    /**
     * Use this method to disconnect the protocol handler. This method is thread-safe and any
     * reimplementation should be too.
     * 
     *  The default implementation will schedule the stopping of the associated session gracefully.
     */
    virtual void disconnect();

    /**
     * This method is called by the associated session if something went wrong. 
     * The handler is no longer usable.
     * 
     * You can use this method to notify an associated client object that the handler is now off.
     * 
     * This code runs in the TCP thread.
     */
    virtual void disconnected();
    
  protected:
    /**
     * Call this function is you protocol handler to request data. When the data you requested
     * becomes available, the bytesAvailable() method will be called.
     * 
     * @return true is the read is scheduled, false otherwise.
     */
    bool request(std::size_t bytes);

  private:
    friend class TcpSession;
    
    /**
     * Use to set the session shared_ptr; This is done when the TcpSession starts, because it
     * can't be done from the session constructor;
     */
    void setSession(std::shared_ptr<TcpSession> session);
    std::weak_ptr<TcpSession> session_;
  };
}
#endif	/* ATCPPROTOCOLHANDLER_HPP */

