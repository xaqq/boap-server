/* 
 * File:   MovableEntity.hpp
 * Author: xaqq
 *
 * Created on November 18, 2013, 11:04 PM
 */

#ifndef MOVABLEENTITY_HPP
#define	MOVABLEENTITY_HPP

#include "world/GameEntity.hpp"
#include "world/PathFindHelper.hpp"

class MovableEntity : public GameEntity
{  
private:
  PathFindHelper pathHelper_;
  float velocity_;
  btVector3 destination_;
  
public:
  MovableEntity(WorldFacade &world, std::shared_ptr<btCollisionShape> shape);
  MovableEntity(const MovableEntity& orig) = delete;
  virtual ~MovableEntity();
  
  bool setDestination(float x, float y, float z);
  const  btVector3 & destination()const;
  bool destinationReached();
  
  /**
   * Move toward the current target. That means that the unit could go backward;
   * If you want the unit to go forward call move() instead;
   * @return 
   */
  bool moveTowardTarget();
  
  /**
   * Move the target;
   */
  bool move();

  virtual  void update(Milliseconds ms);
  
  void velocity(float velocity)
  {
    velocity_ = velocity;
  }

  float velocity() const
  {
    return velocity_;
  }
};

#endif	/* MOVABLEENTITY_HPP */

