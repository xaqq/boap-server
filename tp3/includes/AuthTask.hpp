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
#include "CMSGAuthPacket.hpp"

/***
 * Auth task, spawned by the AuthPacketHandler;
 * This task will run sql code and check result. It acts like a state machine.
 * 
 * It auto handle its lifetime
 */
class AuthTask : public std::enable_shared_from_this<AuthTask>
{
public:
  AuthTask(CMSGAuthPacket packet);
  AuthTask(const AuthTask& orig) = delete;
  virtual ~AuthTask();

  /**
   * First state
   */
  bool start();

  /**
   * second state
   */
  bool waitForResult();
  
  /** 
   * third state
   */
  bool resultAvailable();
  
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
  CMSGAuthPacket packet_;
  bool *sqlResult_;
  

};

#endif	/* AUTHTASK_HPP */

