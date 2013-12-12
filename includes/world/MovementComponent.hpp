/* 
 * File:   MovementComponent.hpp
 * Author: xaqq
 *
 * Created on December 11, 2013, 8:50 PM
 */

#ifndef MOVEMENTCOMPONENT_HPP
#define	MOVEMENTCOMPONENT_HPP

/**
 * The Movement component for entities.
 * 
 * This class holds informations about entity velocity, move direction, path (if any).
 * For example, this component is used by movement related behavior.
 */
class MovementComponent
{
public:
  MovementComponent();
  MovementComponent(const MovementComponent& orig) = delete;
  virtual ~MovementComponent();
private:

};

#endif	/* MOVEMENTCOMPONENT_HPP */

