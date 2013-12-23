/* 
 * File:   Account.hpp
 * Author: xaqq
 *
 * Created on December 20, 2013, 1:44 AM
 */

#ifndef ACCOUNT_HPP
#define	ACCOUNT_HPP

#include <memory>
#include <string>
#include "odb/core.hxx"

namespace DB
{
#pragma db object pointer(std::shared_ptr)

    /**
     * A database model class for an account.
     * 
     * When a Client sucessfully authenticates, the corresponding account class is set
     * to the client's account_ field.
     */
    class Account
    {
    public:

        unsigned long id() const
        {
            return id_;
        }

        const std::string &username() const
        {
            return username_;
        }

        const std::string &password() const
        {
            return password_;
        }

    private:
        friend class odb::access;

#pragma db id auto 
        unsigned long id_;

#pragma db unique\
                    type("VARCHAR(255)")
        std::string username_;
        std::string password_;

    };
}
#pragma db object(DB::Account)
#endif	/* ACCOUNT_HPP */

