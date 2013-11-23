#include <iostream>
#include "Log.hpp"
#include <boost/uuid/random_generator.hpp>
#include "world/GameEntity.hpp"
#include "world/Game.hpp"

#include <BulletCollision/CollisionShapes/btBox2dShape.h>

extern btCollisionWorld *world;

GameEntity::GameEntity(WorldFacade &world, std::shared_ptr<btCollisionShape> shape)
:
world_(world),
affectNavMesh_(true),
shape_(shape)
{
  transform_.setIdentity();
  transform_.setOrigin(btVector3(0, 0, 0));
  object_ = std::make_shared<btCollisionObject > ();
  object_->setCollisionShape(shape_.get());
  object_->setWorldTransform(transform_);
}

GameEntity::~GameEntity()
{
  world_.removeFromCollisionWorld(object_.get());
  DEBUG("Entity " << uuid_() << " destroyed");
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
      btMatrix3x3 matrix(rotation);
      btVector3 pos;

      tmp.setRotation(rotation * child->transform().getRotation());
      pos = tmp.getOrigin();
      pos = pos * matrix;
      tmp.setOrigin(pos);
      child->transform(tmp);
    }
}

bool GameEntity::affectNavMesh() const
{
  return affectNavMesh_;
}

void GameEntity::affectNavMesh(bool v)
{
  affectNavMesh_ = v;
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

bool GameEntity::collideWith(std::shared_ptr<GameEntity>) {
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

void GameEntity::addChild(std::shared_ptr<GameEntity> e)
{
  children_.push_back(e);
}

std::vector<GameEntity::Polygone> GameEntity::getPolygonesForMe()
{
  std::vector<Polygone> res;

  if (!shape_)
    return res;
  if (btBox2dShape * shape = dynamic_cast<btBox2dShape *> (shape_.get()))
    {
      DEBUG("2DSHAPE " << shape->getNumEdges());
      const btMatrix3x3 matrix_rot(transform_.getRotation());
      Polygone p;
      for (int i = 0; i < shape->getNumEdges(); i++)
        {
          btVector3 a;
          btVector3 b;
          shape->getEdge(i, a, b);
          a = a * matrix_rot;
          a += transform_.getOrigin();
          b = b * matrix_rot;
          b += transform_.getOrigin();
          p.push_back(a);
          p.push_back(b);
        }
      res.push_back(p);
    }
  else if (btBoxShape * shape = dynamic_cast<btBoxShape *> (shape_.get()))
    {
      DEBUG("3DSHAPE " << shape->getNumEdges());
      const btMatrix3x3 matrix_rot(transform_.getRotation());
      std::vector<btVector3> pointsInPlane[shape->getNumPlanes()];
      /// blaaaa
      for (int i = 0; i < shape->getNumPlanes(); i++)
        {
          btVector3 normal;
          btVector3 point;

          shape->getPlane(normal, point, i);

          for (int j = 0; j < shape->getNumVertices(); j++)
            {
              btVector3 v1;
              shape->getVertex(j, v1);

              btVector3 diff1;

              diff1 = point - v1;
              btScalar scal1 = diff1.dot(normal);

              if (scal1 == 0)
                {
                  v1 = v1 * matrix_rot;
                  v1 += transform_.getOrigin();
                  pointsInPlane[i].push_back(v1);
                }
            }
        }

      // brute force; take all point for each face and generate polygone
      for (int i = 0; i < shape->getNumPlanes(); ++i)
        {
          for (unsigned int j = 0; j < pointsInPlane[i].size(); ++j)
            {
              Polygone p;
              p.push_back(pointsInPlane[i][j]);
              for (unsigned int k = 0; k < pointsInPlane[i].size(); ++k)
                {
                  if (j == k)
                    continue;
                  p.push_back(pointsInPlane[i][k]);
                }
              res.push_back(p);
            }

        }
    }
  return res;
}

std::vector<GameEntity::Polygone> GameEntity::getPolygones()
{
  std::vector<Polygone> res;

  res = getPolygonesForMe();
  for (auto child : children_)
    {
      auto tmp = child->getPolygones();
      res.insert(res.end(), tmp.begin(), tmp.end());
    }
  return res;
}

void GameEntity::update(Milliseconds diff)
{
  INFO("Updating entity");
}

const btVector3 & GameEntity::position() const
{
  return transform_.getOrigin();
}

void GameEntity::lookAt(float x, float y, float z)
{
  btVector3 dir = btVector3(x, y, z) - transform_.getOrigin();

}
