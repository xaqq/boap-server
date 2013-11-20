/* 
 * File:   World.hpp
 * Author: xaqq
 *
 * Created on November 14, 2013, 5:25 AM
 */

#ifndef WORLD_HPP
#define	WORLD_HPP

#include <future>
#include <list>
#include <memory>
#include "sql/SqlHandler.hpp"
#include "world/EntityFactory.hpp"
#include "world/NavMeshBuilder.hpp"
#include "WorldFacade.hpp"

class ISqlResult;

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btCollisionWorld;

class World : public WorldFacade
{
public:
  World();
  World(const World& orig) = delete;
  virtual ~World();

  std::shared_ptr<GameEntity> spawn(int entityId) override;
  void update();

  void registerOberserver(class IWorldObserver *) override;
  void unregisterObserver(IWorldObserver *) override;

private:

  /**
   * Initialise the world; this is called when the entity factory is ready;
   * @return 
   */
  bool init();
  
  bool initNavhMesh();
  
  /**
   * When the world's entities are created, we build the nav mesh.
   */
  bool buildNavhMesh();


  /**
   * The entity factory for the world.
   * This is not shared between World's instance because it would make it harder to
   * apply database modifications to the future games.
   */
  EntityFactory entityFactory_;

  /**
   * Internal flag, set to true when the navigation meshe and the scene has been built.
   */
  bool ready_;
  SqlFutureResult future_;
  btBroadphaseInterface* broadphase_;
  btDefaultCollisionConfiguration* collisionConfiguration_;
  btCollisionDispatcher* dispatcher_;
  btSequentialImpulseConstraintSolver* solver_;
  btCollisionWorld* collisionWorld_;

  /**
   * All entities in the world.
   */
  std::list<std::shared_ptr<GameEntity >> entities_;
  
  /**
   * The world UUID.
   */
  boost::uuids::uuid uuid_;

  /**
   * This object build the navigation mesh and provide a navMeshQuery used by entity for pathfinding.
   * Therefore, we only construct it when the entityFactory is ready and the map has been built (todo)
   */
  NavMeshBuilder *navMeshBuilder_;

  std::list<IWorldObserver *> observers_;
};

#endif	/* WORLD_HPP */

