/* 
 * File:   DBManager.cpp
 * Author: xaqq
 * 
 * Created on December 20, 2013, 8:10 PM
 */

#include "db/DBManager.hpp"

using namespace DB;

std::shared_ptr<DBManager> DBManager::instance_(nullptr);
                
DBManager::DBManager() :
connectionFactory_(new odb::mysql::connection_pool_factory(20, 0)),
database_(new odb::mysql::database("root", "boap", "boapd", "127.0.0.1", 0, nullptr, nullptr, 0, connectionFactory_))
{

}

DBManager::~DBManager()
{
    
}

DBManager &DBManager::instance()
{
    if (!instance_)
        instance_ = std::shared_ptr<DBManager>(new DBManager());
    return *instance_;
}

