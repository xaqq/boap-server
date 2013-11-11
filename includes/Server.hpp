/* 
 * File:   Server.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 6:24 PM
 */

#ifndef SERVER_HPP
#define	SERVER_HPP

#include <atomic>
#include <memory>
#include <list>
#include "SafeQueue.hpp"
#include "APacket.hpp"

class APacket;
class AClient;
class APacketHandler;

class Server
{
public:
  
  
  typedef std::list<std::shared_ptr<AClient >> ClientList;
  typedef SafeQueue<std::shared_ptr<APacket >> PacketList;
  typedef std::list<std::shared_ptr<APacketHandler >> PacketHandlerList;

  
  Server(const Server& orig) = delete;
  virtual ~Server();

  static Server &instance();

  /**
   * Call to shutdown the server;
   */
  void stop();

  /**
   * Server main loop;
   */
  void run();

  /**
   * Asynchronously add the client to the server's client list.
   * This function is thread safe, because it simply queue the call
   * @param c
   */
  void addClient(std::shared_ptr<AClient> c);

  /**
   * Asynchronously remove the client to the server's client list.
   * This function is thread safe, because it simply queue the call
   * @param c
   */
  void removeClient(std::shared_ptr<AClient> c);

  
  /**
   * This returns the list of client known by the server. This is intended for use by packet handler
   * @return  list of client
   */
  const ClientList &clients() const;
  
  /**
   * Use to schedule a call of f() in the server's thread.
   * This method is thread safe.
   * @param f
   */
  void post(std::function<void() > f)
  {
    operationQueue_.push(f);
  }

  /**
   * Use to push a packet that will be handled later; 
   * This is thread safe;
   */
  void pushPacket(std::shared_ptr<APacket> p)
  {
    packets_.push(p);
  }
  
private:
  Server();
  
  static Server *instance_;

  std::atomic_bool isRunning_;

  ClientList clients_;
  PacketList packets_;
  PacketHandlerList packetHandlers_;

  /**
   * Invoke queued handler;
   */
  void flush_operations();

  void handle_packets();
  
  SafeQueue<std::function<void () >> operationQueue_;
};

#endif	/* SERVER_HPP */

