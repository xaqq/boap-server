/* 
 * File:   EntityFactory.cpp
 * Author: xaqq
 * 
 * Created on November 16, 2013, 12:51 PM
 */

#include <bullet/BulletCollision/CollisionShapes/btBox2dShape.h>

#include "world/EntityFactory.hpp"
#include "Log.hpp"
#include "Scheduler.hpp"
#include "sql/EntityTemplate.hpp"
#include "world/GameEntity.hpp"
#include "world/MovableEntity.hpp"
#include "sql/ShapeTemplate.hpp"

std::map<std::string, EntityFactory::ShapeBuilder> EntityFactory::shapeBuilders_ = {
  {"2dBox", [](const ShapeTemplate & tpl)
    {
      return std::shared_ptr<btCollisionShape > (new btBox2dShape(tpl.params_));
    }}

  ,
  {"3dBox", [](const ShapeTemplate & tpl)
    {
      return std::shared_ptr<btCollisionShape > (new btBoxShape(tpl.params_));
    }}
};

std::map<std::string, EntityFactory::EntityBuilder> EntityFactory::entityBuilders_ = {
  {"GameEntity", &EntityFactory::buildEntityGameEntity},
  {"MovableEntity", &EntityFactory::buildMovableEntity}
};

EntityFactory::EntityFactory(WorldFacade &world) :
world_(world),
ready_(false)
{
  loadShapes();
  loadEntities();
  ready_ = true;
}

EntityFactory::~EntityFactory() { }

void EntityFactory::loadEntities()
{
  INFO("EntityFactory starting to load entities");

  sqlFuture_ = Scheduler::instance()->runFutureInSql([](sql::Connection * sql)
  {
                                                     if (!sql)
                                                     return SqlTaskReturnType(new ISqlResult(true));
                                                     SqlTaskReturnType sql_ret = EntityTemplate::loadAllTemplate(sql);
                                                     return sql_ret;
    });

  std::future_status status;
  status = sqlFuture_.wait_for(Milliseconds(5000));
  if (status != std::future_status::ready)
    {
      ERROR("Loading entity never completed");
      return;
    }
  SqlTaskReturnType ret = sqlFuture_.get();
  if (ret->error() || !ret->result())
    {
      WARN("Error loading entities...");
      delete (reinterpret_cast<std::list<GameEntity> *> (ret->result()));
      return;
    }

  for (auto eTpl : *(reinterpret_cast<std::list<EntityTemplate> *> (ret->result())))
    {
      DEBUG("Loading entity template: id: " << eTpl.id_ << ", name: " << eTpl.name_ << ", script_name: " << eTpl.scriptName_ <<
            " shape_id: " << eTpl.shape_id);
      entities_[eTpl.id_] = eTpl;
    }
  delete (reinterpret_cast<std::list<EntityTemplate> *> (ret->result()));
}

void EntityFactory::loadShapes()
{
  INFO("EntityFactory starting to load shape");

  sqlFuture_ = Scheduler::instance()->runFutureInSql([](sql::Connection * sql)
  {
                                                     if (!sql)
                                                     return SqlTaskReturnType(new ISqlResult(true));
                                                     SqlTaskReturnType sql_ret = ShapeTemplate::loadAllTemplate(sql);
                                                     return sql_ret;
    });

  std::future_status status;
  status = sqlFuture_.wait_for(Milliseconds(5000));
  if (status != std::future_status::ready)
    {
      ERROR("Loading entity never completed");
      return;
    }
  SqlTaskReturnType ret = sqlFuture_.get();

  if (ret->error() || !ret->result())
    {
      WARN("Error loading shapes...");
      delete (reinterpret_cast<std::list<GameEntity> *> (ret->result()));
      ready_ = false;
      return;
    }

  for (auto shape : *(reinterpret_cast<std::list<ShapeTemplate> *> (ret->result())))
    {
      DEBUG("Loading shape template: id: " << shape.id_ << ", name: " << shape.name_ << ", param1: " << shape.params_[0] <<
            ", param2: " << shape.params_[1] << ", param3: " << shape.params_[2]);

      if (shapeBuilders_.find(shape.name_) == shapeBuilders_.end())
        {
          WARN("Cannot find shape builder for shape with name " << shape.name_);
          continue;
        }
      shapes_[shape.id_] = shapeBuilders_[shape.name_](shape);
    }
  delete (reinterpret_cast<std::list<ShapeTemplate> *> (ret->result()));
}

std::shared_ptr<GameEntity> EntityFactory::instanciate(std::size_t id, const btVector3 & position)
{
  if (entities_.find(id) == entities_.end())
    {
      WARN("No template for entity with id = " << id);
      return nullptr;
    }

  EntityTemplate tpl = entities_[id];
  if (entityBuilders_.find(tpl.scriptName_) == entityBuilders_.end())
    {
      WARN("No builder for script_name  = " << tpl.scriptName_);
      return nullptr;
    }
  auto entityPtr = (this->*(entityBuilders_[tpl.scriptName_]))(tpl);

  INFO("Entity factory instanciating");
  entityPtr->setPosition(position);
  return entityPtr;
}

std::shared_ptr<GameEntity> EntityFactory::buildEntityGameEntity(const EntityTemplate & tpl)
{
  std::shared_ptr<GameEntity > e(new GameEntity(world_, shapes_[tpl.shape_id]));
  e->affectNavMesh(tpl.affectNavMesh_);
  DEBUG("OMGLAMA!" << e->affectNavMesh());
  return e;
}

std::shared_ptr<GameEntity> EntityFactory::buildMovableEntity(const EntityTemplate &tpl)
{
  std::shared_ptr<GameEntity > e(new MovableEntity(world_, shapes_[tpl.shape_id]));
  e->affectNavMesh(tpl.affectNavMesh_);
  DEBUG("OMG!" << e->affectNavMesh());
  return e;
}