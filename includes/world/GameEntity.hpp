#pragma once

#include <list>
#include <memory>
#include <bullet/btBulletDynamicsCommon.h>

class GameEntity
{
public:
  GameEntity(std::shared_ptr<btCollisionShape> shape);

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
  void move(float dist);

  /**
   * Add a child to this entity; The entity 3d object must be already added
   * to the world.
   */
  void addChild(std::shared_ptr<GameEntity> e);

public:
  std::list<std::shared_ptr<GameEntity>> children_;
  std::shared_ptr<btCollisionShape>	shape_;
  std::shared_ptr<btCollisionObject>	object_;
  btTransform				transform_;
};
