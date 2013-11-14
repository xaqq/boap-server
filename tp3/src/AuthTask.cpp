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
#include "MotdPacket.hpp"
#include "AClient.hpp"
#include "AuthPacketHandler.hpp"

AuthTask::AuthTask(CMSGAuthPacket packet) : packet_(packet), sqlResult_(nullptr)
{
  internalHandler_ = std::bind(&AuthTask::start, this);
}

AuthTask::~AuthTask()
{
  DEBUG("AuthTask destroyed");
  delete sqlResult_;
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

bool AuthTask::resultAvailable()
{
  MotdPacket *packet = new MotdPacket(nullptr);

  DEBUG(*sqlResult_);
  std::shared_ptr<APacket> ptr(packet);
  // notify user auth went ok;
  if (packet_.source())
    {
      if (*sqlResult_)
        packet->motd_ = "GG AUTH";
      else
        packet->motd_ = "FAIL AUTH";
      packet_.source()->pushPacket(ptr);
      packet_.source()->disconnect();
    }
  return false;
}

SqlTaskReturnType AuthTask::runSqlCode(sql::Connection * c)
{
  INFO("ICI");
  sql::PreparedStatement *pstmt;
  sql::ResultSet *res;
  SqlTaskReturnType ret(new ISqlResult());
  bool *authSucces = new bool(false);
  try
    {
      pstmt = c->prepareStatement("SELECT COUNT(id) as isAuthValid FROM users WHERE username = (?) AND password = (?)");
      pstmt->setString(1, packet_.username_);
      pstmt->setString(2, packet_.password_);
      res = pstmt->executeQuery();
      while (res->next())
        {
          INFO("SQL REPLIES: " << res->getInt("isAuthValid"));
          if (res->getInt("isAuthValid"))
            *authSucces = true;
        }
    }
  catch (sql::SQLException &e)
    {
      delete res;
      delete pstmt;
      delete authSucces;
      ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
      return nullptr;
    }
  ret->error_ = false;
  ret->result_ = authSucces;

  delete res;
  delete pstmt;
  return ret;
}

bool AuthTask::waitForResult()
{
  if (future_.valid())
    {
      std::future_status status;
      status = future_.wait_for(std::chrono::milliseconds(10));
      if (status != std::future_status::ready)
        return true;
      SqlTaskReturnType result = future_.get();
      if (!result)
        {
          WARN("No result at all (callable returned null)");
          return false;
        }
      else if (result->error())
        {
          WARN("Error when processing query");
          return false;
        }
      else if (!result->result())
        {
          WARN("Custom data are null");
          return false;
        }
      internalHandler_ = std::bind(&AuthTask::resultAvailable, this);
      sqlResult_ = static_cast<bool *> (result->result());
      return true;
    }
  return true;
}