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
#include <cppconn/exception.h>
#include <functional>
#include "sql/ISqlResult.hpp"
#include "Log.hpp"
#include "Scheduler.hpp"
#include "Client.hpp"
#include "Uuid.hpp"
#include "packets/SMSGUdpCode.hpp"
#include "packets/SMSGAuth.hpp"
#include "DBManager.hpp"
#include "odb_gen/Account_odb.h"

AuthTask::AuthTask(CMSGAuthPacket packet) : packet_(packet),
status_(Status::START)
{
}

AuthTask::~AuthTask()
{
    DEBUG("AuthTask destroyed");
}

void AuthTask::operator()(void)
{
    switch (status_)
    {
        case Status::START:
            status_ = Status::CHECK_CREDENTIALS;
            schedule(Thread::HELPER);
            break;

        case Status::CHECK_CREDENTIALS:
            checkCredentials();
            status_ = Status::HANDLE_RESULT;
            schedule(Thread::MAIN);
            break;

        case Status::HANDLE_RESULT:
            handleResult();
            break;
    }
}

void AuthTask::handleResult()
{
    std::shared_ptr<Client> client = std::dynamic_pointer_cast<Client > (packet_.source());

    DEBUG("Auth Task completed");
    if (client)
    {
        std::shared_ptr<SMSGAuth> authPacket(new SMSGAuth(packet_.source(), result_));
        client->pushPacket(authPacket);
        if (result_ == SMSGAuthData::OK)
        {
            std::shared_ptr<SMSGUdpCode> udpCodePacket(new SMSGUdpCode(packet_.source()));

            Uuid u;
            client->udpAuthCode(u.toString());
            client->account(resultAccount_);

            udpCodePacket->authCode_ = client->udpAuthCode();
            client->pushPacket(udpCodePacket);
        }
    }
}

void AuthTask::checkCredentials()
{
    try
    {
        
        typedef odb::query<DB::Account> query;
        typedef odb::result<DB::Account> result;

        result_ = SMSGAuthData::INTERNAL_ERROR;
        DB::ptr db = DB::DBManager::instance().db();

        odb::transaction t(db->begin());
        result r(db->query<DB::Account>(query::username == packet_.data_.username()));
        result::iterator i(r.begin());

        if (i != r.end()) // query returned >= 1 entry.
        {
            if (i->password() == packet_.data_.password())
            {
                result_ = SMSGAuthData::OK;
                resultAccount_ = db->load<DB::Account>(i->id());
            }
            else
                result_ = SMSGAuthData::WRONG_PASSWORD;
            return;
        }
        result_ = SMSGAuthData::UNKNOWN_USER;
    }
    catch (const odb::recoverable &r)
    {
        WARN(r.what());
    }
    catch (const odb::exception& e)
    {
        ERROR(e.what());
    }
}