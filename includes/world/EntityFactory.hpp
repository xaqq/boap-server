/* 
 * File:   EntityFactory.hpp
 * Author: xaqq
 *
 * Created on November 16, 2013, 12:51 PM
 */

#ifndef ENTITYFACTORY_HPP
#define	ENTITYFACTORY_HPP

#include <memory>
#include <map>
#include <functional>
#include <bullet/btBulletDynamicsCommon.h>
#include "sql/SqlHandler.hpp"
#include "sql/EntityTemplate.hpp"
#include "sql/ShapeTemplate.hpp"
#include "GameEntity.hpp"
#include "world/WorldFacade.hpp"
class GameEntity;

/**
 * Factory to spawn entity. This factory will load the template from the database.
 */
class EntityFactory
{
private:
  typedef std::function<std::shared_ptr<btCollisionShape>(const ShapeTemplate&) > ShapeBuilder;
  typedef std::shared_ptr<GameEntity> (EntityFactory::*EntityBuilder)(const EntityTemplate&);
    
  /**
   * A reference to the World api.
   */
  WorldFacade &world_;
  
  /**
   * Is the factory busy (doing some (re)loading ?). The factory should not be used while busy.
   */
  bool ready_;


  std::map<std::size_t, std::shared_ptr<btCollisionShape >> shapes_;
  std::map<std::size_t, EntityTemplate> entities_;

  /**
   * Map mapping shape name to a lambda which will construct one
   */
  static std::map<std::string, ShapeBuilder> shapeBuilders_;

  /**
   * Mapping a script name to a builder which will construct one
   */
  static std::map<std::string, EntityBuilder> entityBuilders_;


  std::shared_ptr<GameEntity> buildEntityGameEntity(const EntityTemplate &tpl);
  std::shared_ptr<GameEntity> buildMovableEntity(const EntityTemplate &tpl);


  void loadShapes();
  void loadEntities();

public:
  EntityFactory(WorldFacade &world);
  EntityFactory(const EntityFactory& orig) = delete;
  virtual ~EntityFactory();

  std::shared_ptr<GameEntity> instanciate(std::size_t id, const btVector3 &position);
  SqlFutureResult sqlFuture_;

  bool isReady() const
  {
    return ready_;
  }

};

#endif	/* ENTITYFACTORY_HPP */

