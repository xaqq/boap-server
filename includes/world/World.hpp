/* 
 * File:   World.hpp
 * Author: xaqq
 *
 * Created on November 14, 2013, 5:25 AM
 */

#ifndef WORLD_HPP
#define	WORLD_HPP


class  btBroadphaseInterface;
class  btDefaultCollisionConfiguration;
class  btCollisionDispatcher;
class  btSequentialImpulseConstraintSolver;
class  btCollisionWorld;  
class World
{
public:
  World();
  World(const World& orig);
  virtual ~World();
  
  void spawn();
  void update();
private: 
  btBroadphaseInterface* broadphase_;
  btDefaultCollisionConfiguration* collisionConfiguration_;
  btCollisionDispatcher* dispatcher_;
  btSequentialImpulseConstraintSolver* solver_;
  btCollisionWorld* collisionWorld_;
  
  


};

#endif	/* WORLD_HPP */

