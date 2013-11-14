/* 
 * File:   World.cpp
 * Author: xaqq
 * 
 * Created on November 14, 2013, 5:25 AM
 */

#include "world/World.hpp"
#include <bullet/btBulletDynamicsCommon.h>
#include "AClient.hpp"

World::World()
{
  broadphase_ = new btDbvtBroadphase();
  collisionConfiguration_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collisionConfiguration_);
  solver_ = new btSequentialImpulseConstraintSolver();
  collisionWorld_ = new btCollisionWorld(dispatcher_, broadphase_, collisionConfiguration_);
}

World::World(const World& orig) {
 }

World::~World()
{
  delete collisionWorld_;
  delete solver_;
  delete dispatcher_;
  delete collisionConfiguration_;
  delete broadphase_;
}

void World::spawn() { }

void World::update() { }