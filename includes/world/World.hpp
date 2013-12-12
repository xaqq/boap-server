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
#include <tuple>
#include <memory>
#include "sql/SqlHandler.hpp"
#include "world/EntityFactory.hpp"
#include "world/NavMeshBuilder.hpp"
#include "WorldFacade.hpp"
#include "Uuid.hpp"
#include "observers/IEntityObserver.hpp"

class ISqlResult;

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btCollisionWorld;

class World : public WorldFacade, public IEntityObserver
{
public:
  /**
   * World constructor.
   * @param sceneName;  The name of the scene this world represents.
   */
  World(const std::string &sceneName);
  World(const World& orig) = delete;
  virtual ~World();

  std::shared_ptr<GameEntity> spawn(int entityId) override;
  std::shared_ptr<GameEntity> spawn(int entityId, btVector3 pos, btVector3 rot) override;
  void removeFromCollisionWorld(btCollisionObject *o) override;

  void update();

  void registerOberserver(class IWorldObserver *) override;
  void unregisterObserver(IWorldObserver *) override;

  std::list<std::shared_ptr<GameEntity >> entities() override;
  dtNavMeshQuery *navMeshQuery() override;

private:
  typedef std::list<std::tuple<int, btVector3, btVector3 >> DefaultEntityList;


  /**
   * Load a list of entity id + information that represent the default entities in the scene;
   * This is a blocking sql call;
   * @return 
   */
  bool getDefaultEntitiesFromDatabase();

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
  Uuid uuid_;

  /**
   * This object build the navigation mesh and provide a navMeshQuery used by entity for pathfinding.
   * Therefore, we only construct it when the entityFactory is ready and the map has been built (todo)
   */
  NavMeshBuilder *navMeshBuilder_;

  std::list<IWorldObserver *> observers_;

  std::string sceneName_;

  /**
   * List of default entites. This is setted by the SQL code but the world will be blocking anyway
   * so its safe
   */
  DefaultEntityList defaultList_;


  void onOutOfResource(std::shared_ptr<ResourceEntity> e) override;
  void onSpeak(std::shared_ptr<class GameEntity>, const std::string &str)  override;
};

#endif	/* WORLD_HPP */

