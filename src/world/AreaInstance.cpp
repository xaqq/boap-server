/* 
 * File:   AreaInstance.cpp
 * Author: xaqq
 * 
 * Created on December 23, 2013, 5:33 AM
 */

#include "world/AreaInstance.hpp"
#include "db/DAO.hpp"
#include "world/GameObject.hpp"
#include "behaviors/Behavior.hpp"
#include "behaviors/Callable.hpp"
#include "ParallelNode.h"

AreaInstance::AreaInstance(DB::AreaPtr area)
: running_(true)
, dbData_(new DB::AreaInstance())
{
    dbData_->uuid(uuid_.toString());
    dbData_->areaTemplate(area);
    DEBUG("Persisting AreaInstance entry, " << std::boolalpha << DB::DAO::persist(dbData_));

    using namespace BehaviorTree;
    using namespace Behaviors;

    ParallelNode *brain = new ParallelNode(FAILURE_POLICY::FAIL_ON_ONE);
    RepeatNode *repeat = new RepeatNode(-1);
    repeat->addChild((new SequentialNode())
            ->addChild(new BoolCondition<AreaInstance>(&AreaInstance::stopped, false))
            ->addChild(new Callable < std::function<void() >> (std::bind(&AreaInstance::processPacket, this))));

    PriorityNode *prio = new PriorityNode();
    prio->addChild(repeat);
    prio->addChild(new AlwaysFailure());

    brain->addChild((new SequentialNode())
            ->addChild(new BoolCondition<AreaInstance>(&AreaInstance::initialize, true))
            ->addChild(prio));

    //  ->addChild(repeat));

    behavior_.brain(brain);
}

AreaInstance::~AreaInstance()
{

    DEBUG("DEAD");
}

void AreaInstance::processPacket()
{

    //DEBUG("Process packet placeholder");
}

bool AreaInstance::initialize()
{

    return spawnDefaultGameObjects();
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
    if (DB::DAO::update(dbData_))

        return true;
    return false;
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

bool AreaInstance::update()
{

    return behavior_.update(this);
    //spawnDefaultGameObjects();
}

void AreaInstance::stop()
{

    ERROR("STOPPING GAME");
    running_ = false;
}

void AreaInstance::cleanup()
{
    INFO("Cleaning up game...");
}