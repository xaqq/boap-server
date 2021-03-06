#pragma once

#include <vector>
#include <array>
#include <list>
#include <memory>
#include <boost/uuid/uuid.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include "Clock.hpp"
#include "world/WorldFacade.hpp"
#include "Uuid.hpp"
#include "observers/IEntityObserver.hpp"
#include "observers/Observable.hpp"
#include "behaviors/Behavior.hpp"
#include "world/MovementComponent.hpp"

class GameEntity : public std::enable_shared_from_this<GameEntity>, public Observable<IEntityObserver>
{
public:

  typedef std::vector<btVector3> Polygone;

  GameEntity(WorldFacade &world, std::shared_ptr<btCollisionShape> shape);

  /**
   * Perform clean: - remove itself from the collision world.
   */
  virtual ~GameEntity();

  /**
   * Set the absolute position. This change is not propagated to
   * children.
   */
  void setPosition(const btVector3 &v);

  /**
   * Set the absolute position. This change is not propagated to
   * children.
   */
  void setPosition(btScalar x, btScalar y, btScalar z);

  const btVector3 &position() const;

  /**
   * Set the absolute rotation of the entity. This change is not propagated to
   * children.
   */
  void setRotation(btScalar x, btScalar y, btScalar z);
  /**
   * Set the absolute rotation of the entity. This change is not propagated to
   * children.
   */
  void setRotation(const btQuaternion &q);

  MovementComponent &movement()
  {
    return movement_;
  }

  /**
   * Translate the entity and all children entities.
   */
  void translate(const btVector3& v);
  /**
   * Rotate the entity and all children entities.
   * Angle are in degree.
   */
  void rotate(btScalar x, btScalar y, btScalar z);
  /**
   * Rotate the entity and all children entities.
   */
  void rotate(const btQuaternion &q);

  bool collideWith(std::shared_ptr<GameEntity> e);
  const btTransform &transform() const;
  void transform(const btTransform &t);
  btCollisionObject *object();

  bool affectNavMesh() const;
  void affectNavMesh(bool v);

  const Uuid &uuid() const
  {
    return uuid_;
  }

  /**
   * Rotate the entity so that it looks towards the location
   * TODO
   */
  void lookAt(float x, float y, float z);

  /**
   * Add a child to this entity; The entity 3d object must be already added
   * to the world.
   */
  void addChild(std::shared_ptr<GameEntity> e);

  virtual void update(Milliseconds diff);

  /**
   * Return the list of triangle that represent the geometry of this entity.
   */
  std::vector<Polygone> getPolygonesForMe();

  /**
   * Return the list of triangle that represent this entity and its children.
   */
  std::vector<Polygone> getPolygones();

  /**
   * @return true if is a player, false otherwise
   */
  virtual bool isPlayer() const
  {
    return false;
  };

  WorldFacade &world()
  {
    return world_;
  }

  const WorldFacade &world() const
  {
    return world_;
  }
  
  
  std::shared_ptr<GameEntity> target()
  {
    return target_.lock();
  }
  
  void target(std::shared_ptr<GameEntity> e)
  {
    target_ = e;
  }
  
  std::shared_ptr<GameEntity> toSharedPtr()
  {
    return shared_from_this();
  }
  
protected:

  /**
   * A Reference to the world.
   */
  WorldFacade &world_;

  /**
   * Should this entity be used for building nav-mesh ?
   */
  bool affectNavMesh_;

  /**
   * The entity's behavior. This uses the Libbehavior library to process a behavior tree.
   */
  Behavior behavior_;

private:
  std::list<std::shared_ptr<GameEntity >> children_;
  std::shared_ptr<btCollisionShape> shape_;
  std::shared_ptr<btCollisionObject> object_;
  btTransform transform_;
  std::shared_ptr<GameEntity> parent_;
  Uuid uuid_;
  MovementComponent movement_;

  std::weak_ptr<GameEntity> target_;
  
};
