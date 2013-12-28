/* 
 * File:   AreaInstance.cpp
 * Author: xaqq
 * 
 * Created on December 23, 2013, 5:33 AM
 */

#include "world/AreaInstance.hpp"
#include "db/DAO.hpp"
#include "world/GameObject.hpp"

AreaInstance::AreaInstance(DB::AreaPtr area)
: dbData_(new DB::AreaInstance())
{
    dbData_->uuid(uuid_.toString());
    dbData_->areaTemplate(area);
    DEBUG("Persisting AreaInstance entry, " << std::boolalpha << DB::DAO::persist(dbData_));

    spawnDefaultGameObjects();
}

AreaInstance::~AreaInstance()
{
}

bool AreaInstance::spawnDefaultGameObjects()
{
    for (auto spawnData : DB::DAO::GOSpawnForArea(dbData_->areaTemplate()))
    {
        INFO("Spawn data... " << spawnData->goTemplate()->name());
        GameObject::Ptr ptr(new GameObject(spawnData->goTemplate()));

        dbData_->addGameObject(ptr->dbData());
        gameObjects_.push_back(ptr);
    }
    DB::DAO::update(dbData_);
}

bool AreaInstance::erase()
{
    bool ret = true;
    
    if (dbData_)
    {
        for (auto go : gameObjects_)
        {
            ret &= go->erase();
        }
        ret &= DB::DAO::erase(dbData_);
    }
    return ret;
}