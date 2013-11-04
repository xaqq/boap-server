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

class Server
{
  class AClient;
public:
  Server();
  Server(const Server& orig) = delete;
  virtual ~Server();

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
   * Use to schedule a call of f() in the server's thread.
   * This method is thread safe.
   * @param f
   */
  void post(std::function<void() > f)
  {
    operationQueue_.push(f);
  }

private:
  typedef std::list<std::shared_ptr<AClient>> ClientList;
  std::atomic_bool isRunning_;

  ClientList clients_;
  
  /**
   * Invoke queued handler;
   */
  void flush_operations();

  SafeQueue<std::function<void () >> operationQueue_;
};

#endif	/* SERVER_HPP */

