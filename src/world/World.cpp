/* 
 * File:   World.cpp
 * Author: xaqq
 * 
 * Created on November 14, 2013, 5:25 AM
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "world/World.hpp"
#include <bullet/btBulletDynamicsCommon.h>
#include "AClient.hpp"
#include "Log.hpp"
#include "sql/EntityTemplate.hpp"
#include <functional>
#include <string>
#include "Scheduler.hpp"
#include "sql/ISqlResult.hpp"
#include "world/GameEntity.hpp"
#include <boost/uuid/uuid_io.hpp>
#include "world/RecastConverter.hpp"
#include "world/NavMeshBuilder.hpp"
#include "world/PathFindHelper.hpp"
#include "world/MovableEntity.hpp"
#include "DetourTileCache.h"
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <future>

World::World() :
entityFactory_(*this),
ready_(false),
navMeshBuilder_(nullptr)
{
  broadphase_ = new btDbvtBroadphase();
  collisionConfiguration_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
  solver_ = new btSequentialImpulseConstraintSolver();
  collisionWorld_ = new btCollisionWorld(dispatcher_, broadphase_, collisionConfiguration_);
}

World::~World()
{
  entities_.clear();
  delete solver_;
  delete dispatcher_;
  delete collisionConfiguration_;
  delete broadphase_;
  delete navMeshBuilder_;
  delete collisionWorld_;

  DEBUG("World destroyed");
}

std::shared_ptr<GameEntity> World::spawn(int entityId)
{
  auto e = entityFactory_.instanciate(entityId, btVector3(0, 0, 0));
  if (!e)
    return nullptr;
  collisionWorld_->addCollisionObject(e->object());
  entities_.push_back(e);
  return e;
}

bool World::initNavhMesh()
{
  std::stringstream ss;
  std::ofstream geometryFile;
  RecastConverter converter;

  ss << "/tmp/world." << uuid_() << ".geometry";

  for (auto e : entities_)
    {
      if (e->affectNavMesh())
        {
          DEBUG("add !");
          converter.addEntity(e.get());
        }
    }

  geometryFile.open(ss.str().c_str(), std::ios::trunc);
  geometryFile << converter.genDataDump();
  geometryFile.close();

  navMeshBuilder_ = new NavMeshBuilder(ss.str().c_str());
  // looks like this can SEGV if there is no floor or something
  return navMeshBuilder_->build();
}

bool World::init()
{
  INFO("Initializing world " << uuid_());

  auto floor = spawn(1);
  if (floor)
    floor->rotate(90, 0, 0);

  for (int i = 0; i < 30; i++)
    {
      std::shared_ptr<MovableEntity> e2 = std::dynamic_pointer_cast<MovableEntity > (spawn(2));
      if (e2)
        e2->setDestination(5, 5, 5);
    }

  if (initNavhMesh())
    {
      for (auto o : observers_)
        {
          o->onNavMeshQueryChange(navMeshBuilder_->m_navQuery);
        }
    }
  else
    {
      WARN("Cannot initialize nav mesh");
    }

  return true;
}

void World::update()
{
  if (!ready_)
    {
      if (entityFactory_.isReady())
        ready_ = init();
      else
        return;
    }
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
  for (auto e : entities_)
    {
      e->update(deltaTime());
    }
  deltaTime(true);
}

void World::registerOberserver(IWorldObserver *o)
{
  observers_.push_back(o);
}

void World::unregisterObserver(IWorldObserver *o)
{
  observers_.remove(o);
}

void World::removeFromCollisionWorld(btCollisionObject *o)
{
  collisionWorld_->removeCollisionObject(o);
}