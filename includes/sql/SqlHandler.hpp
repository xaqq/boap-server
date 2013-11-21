/* 
 * File:   SqlHandler.hpp
 * Author: xaqq
 *
 * Created on November 12, 2013, 10:54 PM
 */

#ifndef SQLHANDLER_HPP
#define	SQLHANDLER_HPP

#include <memory>
#include <atomic>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include "SafeQueue.hpp"
#include <future>
#include "sql/ISqlResult.hpp"

typedef std::shared_ptr<ISqlResult> SqlTaskReturnType;
typedef std::packaged_task<SqlTaskReturnType(sql::Connection *) > SqlPackagedTask;
/**
 * Typedef for a future; a ISqlResult is returned by all sql future;
 */
typedef std::future<SqlTaskReturnType> SqlFutureResult;

/**
 * SQL Handlers, should run in its own thread.
 */
class SqlHandler
{
public:
  SqlHandler();
  SqlHandler(const SqlHandler& orig) = delete;
  virtual ~SqlHandler();

  /** Infinite loop */
  void run();

  /**
   * Thread safe, will stop the run infinite loop
   */
  void stop();

  /**
   * Push a callable that will be execute in the sql thread;
   */
  void pushRequest(std::function<void (sql::Connection *)>);
  void pushRequestFuture(SqlPackagedTask f);

private:
  bool connect();

  std::atomic_bool run_;
  sql::Driver *driver_;
  std::shared_ptr<sql::Connection> connection_;


  /**
   * The handler stores a list of callable that contains code that requires the sql thread to run.
   * It provide the connection object;
   */
  SafeQueue<std::function<void (sql::Connection *) >> requests_;
  SafeQueue<SqlPackagedTask> requestsFuture_;
};

#endif	/* SQLHANDLER_HPP */

