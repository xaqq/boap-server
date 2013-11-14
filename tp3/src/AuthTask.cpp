/* 
 * File:   AuthTask.cpp
 * Author: xaqq
 * 
 * Created on November 14, 2013, 9:07 AM
 */

#include "AuthTask.hpp"
#include <future>
#include <cppconn/resultset.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <functional>
#include "sql/ISqlResult.hpp"
#include <cppconn/exception.h>
#include "Log.hpp"
#include "Scheduler.hpp"
#include "AuthPacketHandler.hpp"

AuthTask::AuthTask()
{
  internalHandler_ = std::bind(&AuthTask::start, this);
}

AuthTask::AuthTask(const AuthTask& orig) { }

AuthTask::~AuthTask()
{
  DEBUG("AuthTask destroyed");
}

void AuthTask::operator()(void)
{
  if (internalHandler_())
    Scheduler::instance()->runInServerThread(std::bind(&AuthTask::operator (), shared_from_this()));
}

bool AuthTask::start()
{
  future_ = Scheduler::instance()->runFutureInSql(std::bind(&AuthTask::runSqlCode, this, std::placeholders::_1));
  internalHandler_ = std::bind(&AuthTask::waitForResult, this);
  return true;
}

SqlTaskReturnType AuthTask::runSqlCode(sql::Connection *c)
{
  sleep(3);
  INFO("ICI");
  sql::PreparedStatement *pstmt;
  sql::ResultSet *res;
  try
    {
      pstmt = c->prepareStatement("SELECT COUNT(id) as isAuthValid FROM users WHERE username = (?) AND password = (?)");
      pstmt->setString(1, "toto");
      pstmt->setString(2, "toto");
      res = pstmt->executeQuery();
      while (res->next())
        {
          INFO("SQL REPLIES: " << res->getInt("isAuthValid"));
        }
    }
  catch (sql::SQLException &e)
    {
      ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
      return nullptr;
    }
  ISqlResult *ptr = new ISqlResult();
  ptr->error_ = false;
  //  ptr->result_ = e;

  delete res;
  delete pstmt;
  // std::shared_ptr<ISqlResult> temp(ptr);
  //DEBUG("BOAP:" << temp.get());
  return SqlTaskReturnType(ptr);
}

bool AuthTask::waitForResult()
{
  if (future_.valid())
    {
      std::future_status status;
      status = future_.wait_for(std::chrono::milliseconds(0));
      if (status != std::future_status::ready)
        return true;
      SqlTaskReturnType result = future_.get();
      INFO("Future Auth !!");
      if (result && !result->error())
        {
          //          EntityTemplate *tpl = reinterpret_cast<EntityTemplate *> (result.get()->result());
          //         DEBUG("FUTURE!: " << tpl->name_);
          //          delete tpl;
        }
      else
        {
          return false;
        }
    }
  return true;
}