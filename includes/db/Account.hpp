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

namespace DB {
#pragma db object pointer(std::shared_ptr)
class Account {
    private:
        friend class odb::access;

#pragma db id auto 
        unsigned long id_;

        std::string username_;
        std::string password_;

    };
}
#pragma db object(DB::Account)
#endif	/* ACCOUNT_HPP */

