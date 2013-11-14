/* 
 * File:   AuthTask.hpp
 * Author: xaqq
 *
 * Created on November 14, 2013, 9:07 AM
 */

#ifndef AUTHTASK_HPP
#define	AUTHTASK_HPP


#include <memory>
#include "sql/SqlHandler.hpp"

/***
 * Auth task, spawned by the AuthPacketHandler;
 * This task will run sql code and check result. It acts like a state machine.
 * 
 * It auto handle its lifetime
 */
class AuthTask : public std::enable_shared_from_this<AuthTask>
{
public:
  AuthTask();
  AuthTask(const AuthTask& orig);
  virtual ~AuthTask();

  /**
   * First state
   */
  bool start();

  /**
   * second state
   */
  bool waitForResult();
  
  SqlTaskReturnType runSqlCode(sql::Connection *);

  /**
   * If the internal handler returns false the task will stop registering itself.
   */
  void operator()(void);

private:
  /**
   * Method pointer to handler.
   */
  std::function<bool () > internalHandler_;
  /**
   * Sql result
   */
  SqlFutureResult future_;
  
  

};

#endif	/* AUTHTASK_HPP */

