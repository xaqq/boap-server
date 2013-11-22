/* 
 * File:   SqlHandler.cpp
 * Author: xaqq
 * 
 * Created on November 12, 2013, 10:54 PM
 */

#include "sql/SqlHandler.hpp"
#include <chrono>
#include "Log.hpp"
#include <cppconn/exception.h>
#include <mysql/mysql.h>
#include <thread>
#include <future>

SqlHandler::SqlHandler() : run_(true) { }

SqlHandler::~SqlHandler()
{
  DEBUG("SqlHandler destroyed");
}

bool SqlHandler::connect()
{
  try
    {
      connection_ = std::shared_ptr<sql::Connection > (driver_->connect("tcp://127.0.0.1:3306", "root", "root"));
      /* Connect to the MySQL test database */
      connection_->setSchema("boapd");
      return true;
    }
  catch (sql::SQLException &e)
    {
      ERROR("SQL Exception (When connecting to the database): " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
      connection_.reset();
    }
  return false;
}

void SqlHandler::run()
{
  driver_ = get_driver_instance();
  connect();
  while (run_)
    {
      std::function<void (sql::Connection *) > f;

      if (!connection_)
        {
          connect();
        }

      while (requests_.tryPop(f))
        {
          try
            {
              f(connection_.get());
            }
          catch (sql::SQLException &e)
            {
              ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
            }
        }

      SqlPackagedTask pt;
      while (requestsFuture_.tryPop(pt))
        {
          try
            {
              pt(connection_.get());
            }
          catch (sql::SQLException &e)
            {
              ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
            }
        }
      std::chrono::milliseconds dura(200);
      std::this_thread::sleep_for(dura);
    }
  mysql_thread_end();
}

void SqlHandler::stop()
{
  run_ = false;
}

void SqlHandler::pushRequest(std::function<void (sql::Connection *) > f)
{
  requests_.push(f);
}

void SqlHandler::pushRequestFuture(SqlPackagedTask f)
{
  requestsFuture_.push(std::move(f));
}
