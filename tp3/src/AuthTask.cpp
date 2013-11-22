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
#include <boost/uuid/uuid.hpp>
#include "Log.hpp"
#include "Scheduler.hpp"
#include "MotdPacket.hpp"
#include "AClient.hpp"
#include "Client.hpp"
#include "AuthPacketHandler.hpp"
#include "SMSGUdpCode.hpp"
#include "Uuid.hpp"
#include "SMSGAuth.hpp"

AuthTask::AuthTask(CMSGAuthPacket packet) : packet_(packet)
{
  internalHandler_ = std::bind(&AuthTask::start, this);
}

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

bool AuthTask::resultAvailable()
{
  std::shared_ptr<Client> client = std::dynamic_pointer_cast<Client > (packet_.source());

  DEBUG("Auth Task completed");
  if (client)
    {
      std::shared_ptr<SMSGAuth> authPacket(new SMSGAuth(packet_.source(), result_));
      client->pushPacket(authPacket);
      if (result_ == AuthResult::OK)
        {
          std::shared_ptr<SMSGUdpCode> udpCodePacket(new SMSGUdpCode(packet_.source()));

          Uuid u;
          client->udpAuthCode(u.toString());
          client->username(packet_.username_);
          client->authenticated(true);

          udpCodePacket->authCode_ = client->udpAuthCode();
          client->pushPacket(udpCodePacket);
        }
    }
  return false;
}

SqlTaskReturnType AuthTask::runSqlCode(sql::Connection * c)
{

  std::shared_ptr<ISqlResult> resultWrapper(new ISqlResult());

  if (!c)
    return resultWrapper;

  try
    {
      int count = 0;
      std::shared_ptr<sql::PreparedStatement> pstmt(c->prepareStatement("SELECT password FROM users WHERE username = (?)"));
      std::shared_ptr<sql::ResultSet> res;
      pstmt->setString(1, packet_.username_);

      res = std::shared_ptr<sql::ResultSet > (pstmt->executeQuery());
      while (res->next())
        {
          if (res->getString("password") == packet_.password_)
            result_ = AuthResult::OK;
          else
            result_ = AuthResult::WRONG_PASSWORD;
          count++;
        }
      if (count == 0)
        result_ = AuthResult::UNKNOWN_USER;
      resultWrapper->error_ = false;
      resultWrapper->result_ = nullptr; // no custom data because they are embeded in class

      return resultWrapper;
    }
  catch (sql::SQLException &e)
    {
      ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
      resultWrapper->error_ = true;
      resultWrapper->result_ = nullptr;
      return resultWrapper;
    }

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
      if (!result)
        {
          WARN("No result at all (callable returned null)");
          return false;
        }
      else if (result->error())
        {
          WARN("Error when processing query");
          packet_.source()->pushPacket(std::shared_ptr<APacket>(new SMSGAuth(packet_.source(), AuthResult::INTERNAL_ERROR)));
          return false;
        }
      return resultAvailable();
    }
  return true;
}