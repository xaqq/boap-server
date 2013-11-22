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

class GameEntity
{
public:
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
  std::vector<std::array<btVector3, 3 >> getTrianglesForMe();

  /**
   * Return the list of triangle that represent this entity and its children.
   */
  std::vector<std::array<btVector3, 3 >> getTriangles();
  ;

protected:
  /**
   * A Reference to the world.
   */
  WorldFacade &world_;

  /**
   * Should this entity be used for building nav-mesh ?
   */
  bool affectNavMesh_;

private:
  std::list<std::shared_ptr<GameEntity >> children_;
  std::shared_ptr<btCollisionShape> shape_;
  std::shared_ptr<btCollisionObject> object_;
  btTransform transform_;
  std::shared_ptr<GameEntity> parent_;
  Uuid uuid_;

};
