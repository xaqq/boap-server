/* 
 * File:   Client.hpp
 * Author: xaqq
 *
 * Created on November 3, 2013, 5:40 PM
 */

#ifndef CLIENT_HPP
#define	CLIENT_HPP

#include <string>
#include <memory>
#include "ProtobufDef.hpp"
#include "AClient.hpp"
#include "observers/AMainThreadInstanceObserver.hpp"
#include "db/Account.hpp"

class AreaInstance;;

class Client : public AClient
{
public:
    Client();
    Client(const Client& orig) = delete;
    virtual ~Client();

    /**
     * This is a helper class for a client to observer a main. Allow for a easy workaround around
     * the multiple inheritance of shared_from_this();
     * 
     */
    class GameObserver : public AMainThreadInstanceObserver
    {
    private:
        /**
         * This means that someone joined the game this client is in
         */
        void onClientJoined(std::shared_ptr<AreaInstance>, std::shared_ptr<Client> c);
        void onInstanceStopped(std::shared_ptr<AreaInstance>, SMSGGameStatus::Status st);
    };

    friend class GameObserver;
private:
    /**
     * Observer instance
     */
    std::shared_ptr<GameObserver> observer_;

    /**
     * The account database entry of the client, if any.
     */
    std::shared_ptr<DB::Account> account_;

    std::string udpAuthCode_;

public:

    void udpAuthCode(std::string code);
    const std::string &udpAuthCode() const;

    std::string username() const
    {
        if (account_)
            return account_->username();
        return "NO_USERNAME";
    }

    void account(std::shared_ptr<DB::Account> a)
    {
        account_ = a;
    }

    std::shared_ptr<DB::Account> account()
    {
        return account_;
    }

    bool authenticated() const
    {
        return account_ ? true : false;
    }

};

#endif	/* CLIENT_HPP */

