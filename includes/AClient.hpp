/* 
 * File:   AClient.hpp
 * Author: xaqq
 *
 * Created on November 3, 2013, 5:43 PM
 */

#ifndef ACLIENT_HPP
#define	ACLIENT_HPP

#include <memory>

class APacket;

class AClient
{
public:
  AClient();
  AClient(const AClient& orig) = delete;
  virtual ~AClient();

  virtual void pushPacket(std::shared_ptr<APacket> p) = 0;

  /**
   * Call to disconnect the client;
   */
  virtual void disconnect() = 0;
private:

};

#endif	/* ACLIENT_HPP */

