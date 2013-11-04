/* 
 * File:   Server.hpp
 * Author: xaqq
 *
 * Created on October 29, 2013, 6:24 PM
 */

#ifndef SERVER_HPP
#define	SERVER_HPP

#include <atomic>

#include "SafeQueue.hpp"

class Server
{
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

//  std::shared_ptr<AClient> newClient();
  
  template <typename Signature>
  void post(std::function<Signature> f)
  {
    operationQueue_.push(f);
  }
  
private:
  std::atomic_bool isRunning_;
  
  
  /**
   * Invoke queued handler;
   */
  void flush_operations();

  SafeQueue<std::function<void ()>>  operationQueue_;
};

#endif	/* SERVER_HPP */

