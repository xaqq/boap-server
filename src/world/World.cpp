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
#include "sql/SqlHandler.hpp"
#include "exceptions/WorldFailedInit.hpp"
#include "world/ResourceEntity.hpp"
#include <cppconn/exception.h>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <future>

World::World(const std::string &sceneName) :
entityFactory_(*this),
ready_(false),
navMeshBuilder_(nullptr),
sceneName_(sceneName)
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
  e->registerObserver(shared_from_this());
  entities_.push_back(e);
  return e;
}

std::shared_ptr<GameEntity>World::spawn(int entityId, btVector3 pos, btVector3 rot)
{
  auto e = spawn(entityId);
  if (!e)
    return nullptr;

  e->rotate(rot[0], rot[1], rot[2]);
  e->setPosition(pos);
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

bool World::getDefaultEntitiesFromDatabase()
{

  auto future = Scheduler::instance()->runFutureInSql([this](sql::Connection * c)
  {
                                                      std::shared_ptr<ISqlResult> resultWrapper(new ISqlResult());
                                                      if (!c)
                                                      return resultWrapper;

                                                      try
        {
                                                      /** check if the scene exists */

                                                      std::shared_ptr<sql::PreparedStatement> pstmt(c->prepareStatement("SELECT id FROM scenes WHERE name = (?)"));
                                                      std::shared_ptr<sql::ResultSet> res;

                                                      pstmt->setString(1, sceneName_);
                                                      res = std::shared_ptr<sql::ResultSet > (pstmt->executeQuery());
                                                      if (!res->rowsCount())
                                                      throw WorldFailedInit("Scene does not exist");

                                                      pstmt = std::shared_ptr<sql::PreparedStatement > (c->prepareStatement("SELECT template_id, pos_x, pos_y, pos_z, rot_x, rot_y, rot_z FROM entities WHERE scene_id = (SELECT id FROM scenes WHERE name = (?))"));
                                                      pstmt->setString(1, sceneName_);
                                                      res = std::shared_ptr<sql::ResultSet > (pstmt->executeQuery());
                                                      while (res->next())
              {
                                                      defaultList_.push_back(std::make_tuple(res->getInt("template_id"),
                                                                                             btVector3(res->getDouble("pos_x"), res->getDouble("pos_y"), res->getDouble("pos_z")),
                                                                                             btVector3(res->getDouble("rot_x"), res->getDouble("rot_y"), res->getDouble("rot_z"))));
              }

                                                      resultWrapper->error_ = false;
                                                      resultWrapper->result_ = nullptr;

                                                      return resultWrapper;
        }
                                                      catch (sql::SQLException &e)
        {
                                                      ERROR("SQL Exception:" << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )");
                                                      resultWrapper->error_ = true;
                                                      resultWrapper->result_ = nullptr;
                                                      return resultWrapper;
        }
  });

  if (future.valid())
    {
      std::future_status status;
      status = future.wait_for(std::chrono::milliseconds(15000));
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
        return false;

      if (future.get()->error_ == true)
        {
          throw WorldFailedInit("Sql error while loading entities");
          ERROR("Error when loading default entities");
          return false;
        }
      return true;
    }
  return false;
}

bool World::init()
{
  INFO("Initializing world " << uuid_() << ". Scene: " << sceneName_);

  bool ret = getDefaultEntitiesFromDatabase();
  if (!ret)
    return false;

  for (auto entityToBuild : defaultList_)
    {
      auto entity = spawn(std::get < 0 > (entityToBuild),
                          std::get < 1 > (entityToBuild),
                          std::get < 2 > (entityToBuild));
      if (!entity)
        throw WorldFailedInit("Failed to spawn one the defaults entities");
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
      return false;
    }

  return true;
}

void World::update()
{
  if (!ready_)
    {
      if (entityFactory_.isReady())
        {
          ready_ = init();
          deltaTime(true);
        }
      else
        return;
    }
  for (auto e : entities_)
    {
      e->update(deltaTime());
    }
  deltaTime(true);
}

dtNavMeshQuery *World::navMeshQuery()
{
  if (navMeshBuilder_)
    return navMeshBuilder_->m_navQuery;
  return nullptr;
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

std::list<std::shared_ptr<GameEntity >> World::entities()
{
  return entities_;
}

void World::onOutOfResource(std::shared_ptr<ResourceEntity> e)
{
  DEBUG("Entity went out of resource");
  entities_.remove(std::dynamic_pointer_cast<GameEntity > (e));
  
  auto n = spawn(3);
  
  n->setPosition(rand() % 100, 0, rand() % 100);
}

  void World::onSpeak(std::shared_ptr<GameEntity> e, const std::string &str) 
  {
    INFO("Entity "<< e->uuid()() << " said : " << str);
  }