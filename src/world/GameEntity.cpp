#include <iostream>
#include "Log.hpp"
#include <boost/uuid/random_generator.hpp>
#include "world/GameEntity.hpp"

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

std::vector<std::array<btVector3, 3 >> GameEntity::getTrianglesForMe()
{
  typedef std::array<btVector3, 3 > Triangle;
  std::vector<Triangle> res;

  if (!shape_)
    return res;
  if (btBox2dShape * shape = dynamic_cast<btBox2dShape *> (shape_.get()))
    {
      btVector3 vertex[4];
      const btMatrix3x3 matrix_rot(transform_.getRotation());

      for (int i = 0; i < 4; i++)
        {
          shape->getVertex(i, vertex[i]);
          vertex[i] = vertex[i] * matrix_rot;
          vertex[i] += transform_.getOrigin();
        }

      for (int i = 0; i < 4; i++)
        {
          for (int j = 0; j < 4; j++)
            {
              for (int k = 0; k < 4; k++)
                {
                  if (i != j && i != k && k != j)
                    {
                      res.push_back(Triangle{
                        {vertex[i], vertex[j], vertex[k]}});
                    }
                }
            }
        }


      //      res.push_back(Triangle{vertex[0], vertex[1], vertex[3]});
      //      res.push_back(Triangle{vertex[3], vertex[2], vertex[0]});
    }
  else if (btBoxShape * shape = dynamic_cast<btBoxShape *> (shape_.get()))
    {
      btVector3 vertex[8];
      const btMatrix3x3 matrix_rot(transform_.getRotation());

      //      std::cout << shape->getNumVertices();
      for (int i = 0; i < 8; i++)
        {
          shape->getVertex(i, vertex[i]);
          vertex[i] = vertex[i] * matrix_rot;
          vertex[i] += transform_.getOrigin();
          //	  std::cout << "LOL " << vertex[i][0] << " " << vertex[i][1] << " " << vertex[i][2] << std::endl;
        }
      for (int i = 0; i < 8; i++)
        {
          for (int j = 0; j < 8; j++)
            {
              for (int k = 0; k < 8; k++)
                {
                  if (i != j && i != k && k != j)
                    {
                      res.push_back(Triangle{
                        {vertex[i], vertex[j], vertex[k]}});
                    }
                }
            }
        }

      // res.push_back(Triangle{vertex[0], vertex[1], vertex[3]});
      // res.push_back(Triangle{vertex[3], vertex[2], vertex[0]});

      // res.push_back(Triangle{vertex[4], vertex[5], vertex[7]});
      // res.push_back(Triangle{vertex[7], vertex[6], vertex[4]});

      // res.push_back(Triangle{vertex[0], vertex[1], vertex[6]});
      // res.push_back(Triangle{vertex[6], vertex[7], vertex[0]});
    }
  return res;
}

std::vector<std::array<btVector3, 3 >> GameEntity::getTriangles()
{
  typedef std::array<btVector3, 3 > Triangle;
  std::vector<Triangle> res;

  res = getTrianglesForMe();
  for (auto child : children_)
    {
      auto tmp = child->getTriangles();
      res.insert(res.end(), tmp.begin(), tmp.end());
    }
  return res;
}

void GameEntity::update(Milliseconds diff)
{
  INFO("Updating entity");
}

const btVector3 &GameEntity::position() const
{
  return transform_.getOrigin();
}

void GameEntity::lookAt(float x, float y, float z)
{
  btVector3 dir = btVector3(x, y, z) - transform_.getOrigin();

}