/* 
 * File:   Client.hpp
 * Author: xaqq
 *
 * Created on November 3, 2013, 5:40 PM
 */

#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <memory>
#include "AClient.hpp"
namespace Net
{
class ITcpProtocolHandler;
}
class Client : public AClient, public std::enable_shared_from_this<AClient>
{
public:
  Client();
  Client(const Client& orig) = delete;
  virtual ~Client();
  virtual void pushPacket(std::shared_ptr<APacket> p);
  
  virtual void disconnect();
  
  std::weak_ptr<Net::ITcpProtocolHandler> tcpHandler_;

};

#endif	/* CLIENT_HPP */

