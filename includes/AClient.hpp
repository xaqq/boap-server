/* 
 * File:   AClient.hpp
 * Author: xaqq
 *
 * Created on November 3, 2013, 5:43 PM
 */

#ifndef ACLIENT_HPP
#define	ACLIENT_HPP

#include <memory>

#include "net/ATcpProtocolHandler.hpp"

class APacket;
namespace Net
{
  class ATcpProtocolHandler;
  class AUdpProtocolHandler;
}

class AClient : public std::enable_shared_from_this<AClient>
{
public:
  AClient();
  AClient(const AClient& orig) = delete;
  virtual ~AClient();

  virtual void pushPacket(std::shared_ptr<APacket> p);

  /**
   *  Disconnect a client.
   */
  virtual void disconnect();


  /**
   * Called by the handler if something went wrong (ie, tcpHandler is now invalid);
   * 
   * The handler schedule the call so that it takes place in the server thread, not in the tcp thread.
   */
  virtual void disconnected();

  /**
   * The UDP "connection" timeout. (ie, udpHandler is now invalid)
   */
  virtual void timeout();


  void tcpHandler(std::shared_ptr<Net::ATcpProtocolHandler> handler);
  std::shared_ptr<Net::ATcpProtocolHandler> tcpHandler();

  void udpHandler(std::shared_ptr<Net::AUdpProtocolHandler> handler);
  std::shared_ptr<Net::AUdpProtocolHandler> udpHandler();

protected:
  std::weak_ptr<Net::ATcpProtocolHandler> tcpHandler_;
  std::weak_ptr<Net::AUdpProtocolHandler> udpHandler_;

};

#endif	/* ACLIENT_HPP */

