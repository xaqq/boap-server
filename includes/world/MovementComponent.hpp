/* 
 * File:   MovementComponent.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 8:50 PM
 */

#ifndef MOVEMENTCOMPONENT_HPP
#define	MOVEMENTCOMPONENT_HPP

#include "world/PathFindHelper.hpp"
#include "GameEntity.hpp"

/**
 * The Movement component for entities.
 * 
 * This class holds informations about entity velocity, move direction, path (if any).
 * For example, this component is used by movement related behavior.
 */
class MovementComponent
{
  
private:
  class GameEntity &me_;
  PathFindHelper pathHelper_;
  float velocity_;
  btVector3 destination_;
  
public:
  MovementComponent(GameEntity &e);
  MovementComponent(const MovementComponent& orig) = delete;
  virtual ~MovementComponent();
  
  /**
   * Set the destination the entity should move to.
   * This is the targeted destination point -- To not retrieve destination
   * to move toward it. Use the nextPoint() method;
   * @param x
   * @param y
   * @param z
   * @return True if destination if valid, false otherwise 
   */
  bool setDestination(float x, float y, float z);
  bool setDestination(btVector3 dest);
  const  btVector3 & destination()const;
  bool destinationReached();
  
  /**
   * Retrieve the next point on the path.
   * If the path is invalid, this returns the entity position.
   * @return The point to go to, or the current position.
   */
  btVector3 nextPoint();
  
  /**
   * Behavior will call this method to notify the component that the position of the entity changed.
   */
  bool positionUpdated();
  
  bool canMove() const
  {
    return true;
  }
  
  void velocity(float velocity)
  {
    velocity_ = velocity;
  }

  float velocity() const
  {
    return velocity_;
  }
};

#endif	/* MOVEMENTCOMPONENT_HPP */

