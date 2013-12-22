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
#include "packets/CMSGAuthPacket.hpp"
#include "db/Account.hpp"
#include "ATask.hpp"

/***
 * Auth task, spawned by the AuthPacketHandler;
 * This task will run sql code and check result. It acts like a state machine.
 * 
 * It auto handle its lifetime
 */
class AuthTask : public ATask
{
public:
    AuthTask(CMSGAuthPacket packet);
    AuthTask(const AuthTask& orig) = delete;
    virtual ~AuthTask();

    /**
     * If the internal handler returns false the task will stop registering itself.
     */
    void operator()(void);

private:

    CMSGAuthPacket packet_;

    enum class Status
    {
        START, // when the task first starts (main thread)
        CHECK_CREDENTIALS, // when we should run the sql code (helper thread)
        HANDLE_RESULT // handling the result. (main thread)
    };

    Status status_;

    /**
     * Query the database, check credentials and set the auth result in the result_ member.
     * It also set the resultAccount_ field to a valid account if the auth was sucessful.
     */
    void checkCredentials();

    /**
     * Handle the auth result in the main thread, updating the client object who originated the 
     * request (and therfore the task) if necessary.
     */
    void handleResult();

    /**
     * Authentification result; This is set by the sql code;
     */
    SMSGAuthData::AuthResult result_;

    /**
     * The resulting account (ie the authenfication was successful). On completion, the task will
     * set the resultAccount_ pointer to the account_ field of the client.
     */
    std::shared_ptr<DB::Account> resultAccount_;
};

#endif	/* AUTHTASK_HPP */

