/* 
 * File:   GameObject.cpp
 * Author: xaqq
 * 
 * Created on December 28, 2013, 2:12 AM
 */

#include "world/GameObject.hpp"

GameObject::GameObject(DB::GameObjectTemplatePtr goTemplate) :
dbData_(new DB::GameObject())
{
    DB::StatSheetPtr statSheet(new DB::StatSheet());

    if (goTemplate->baseStats())
        *(statSheet) = *(goTemplate->baseStats());
    DB::DAO::persist(statSheet);

    dbData_->stats(statSheet);
    dbData_->uuid(uuid_.toString());
    dbData_->level(goTemplate->baseLevel());

    DB::DAO::persist(dbData_);
}

GameObject::~GameObject()
{
}

bool GameObject::erase()
{
    bool ret = true;

    if (!dbData_)
        return true;

    ret &= DB::DAO::erase(dbData_->stats());
    ret &= DB::DAO::erase(dbData_);
    return ret;
}
