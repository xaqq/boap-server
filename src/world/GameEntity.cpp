#include <iostream>
#include "world/GameEntity.hpp"

extern btCollisionWorld *world;

GameEntity::GameEntity(std::shared_ptr<btCollisionShape> shape)
  : shape_(shape)
{
  transform_.setIdentity();
  transform_.setOrigin(btVector3(0, 0, 0));
  object_ = std::make_shared<btCollisionObject>();
  object_->setCollisionShape(shape_.get());
  object_->setWorldTransform(transform_);
}

void GameEntity::move(float dist)
{
  btVector3 dst(dist, 0, 0);
  btMatrix3x3 m(transform_.getRotation());
  
  dst = m * dst;
  std::cout << "Move:" << dst[0] << ", " << dst[1] << ", " << dst[2] << std::endl;
  translate(dst);
}

void GameEntity::translate(const btVector3& v)
{
  transform_.setOrigin(transform_.getOrigin() + v);
  object_->setWorldTransform(transform_);
  for (auto child : children_)
    child->translate(v);
}

void GameEntity::rotate(const btQuaternion &rotation)
{
  transform_.setRotation(rotation * transform_.getRotation());
  object_->setWorldTransform(transform_);
  for (auto child : children_)
    {
      btTransform tmp = child->transform();
      btMatrix3x3 matrix (rotation);
      btVector3 pos;

      tmp.setRotation(rotation * child->transform().getRotation());
      pos = tmp.getOrigin();
      pos = pos * matrix;
      tmp.setOrigin(pos);
      child->transform(tmp);
    }
}

void GameEntity::rotate(btScalar x, btScalar y, btScalar z)
{
  btQuaternion rotation(btRadians(y), btRadians(x), btRadians(z));
  rotate(rotation);
}

void GameEntity::setRotation(btScalar x, btScalar y, btScalar z)
{
  btQuaternion rotation(btRadians(y), btRadians(x), btRadians(z));
  setRotation(rotation);
}

void GameEntity::setRotation(const btQuaternion &q)
{
  transform_.setRotation(q);
  object_->setWorldTransform(transform_);
}

void GameEntity::setPosition(const btVector3 &v)
{
  transform_.setOrigin(v);
  object_->setWorldTransform(transform_);
}

void GameEntity::setPosition(btScalar x, btScalar y, btScalar z)
{
  setPosition(btVector3(x, y, z));
}

bool GameEntity::collideWith(std::shared_ptr<GameEntity> e)
{
//  ContactEntityPair c;
//  world->contactPairTest(object(), e->object(), c);
//  return c.result();
}

const btTransform &GameEntity::transform() const
{
  return transform_;
}

void GameEntity::transform(const btTransform &t)
{
  transform_ = t;
  object_->setWorldTransform(transform_);
}

btCollisionObject *GameEntity::object()
{
  return object_.get();
}

void	GameEntity::addChild(std::shared_ptr<GameEntity> e)
{
  children_.push_back(e);
}
