/* 
 * File:   World.cpp
 * Author: xaqq
 * 
 * Created on November 14, 2013, 5:25 AM
 */

#include "world/World.hpp"
#include <bullet/btBulletDynamicsCommon.h>
#include "AClient.hpp"
#include "Log.hpp"
#include "sql/EntityTemplate.hpp"
#include "Scheduler.hpp"
#include "sql/ISqlResult.hpp"
#include <future>

World::World()
{
  broadphase_ = new btDbvtBroadphase();
  collisionConfiguration_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
  solver_ = new btSequentialImpulseConstraintSolver();
  collisionWorld_ = new btCollisionWorld(dispatcher_, broadphase_, collisionConfiguration_);
}

World::World(const World& orig) { }

World::~World()
{
  delete collisionWorld_;
  delete solver_;
  delete dispatcher_;
  delete collisionConfiguration_;
  delete broadphase_;
}

void World::spawn()
{
  INFO("ici");

  future_ = Scheduler::instance()->runFutureInSql([](sql::Connection * sql)
  {
                                                  return EntityTemplate::loadTemplate(sql, 1);

  });

}

void World::update()
{

  if (future_.valid())
    {
      std::future_status status;
      status = future_.wait_for(std::chrono::milliseconds(10));
      if (status == std::future_status::deferred)
        {
          WARN("DEFFERED");
        }
      else if (status == std::future_status::timeout)
        {
          WARN("TIMEOUT");
        }
      else if (status == std::future_status::ready)
        {
          INFO("READY !!");
        }
      if (status != std::future_status::ready)
        return;
      SqlTaskReturnType result = future_.get();
      if (!result->error())
        {
          EntityTemplate *tpl = reinterpret_cast<EntityTemplate *> (result.get()->result());
          DEBUG("FUTURE!: " << tpl->name_);
          delete tpl;
        }
    }
}