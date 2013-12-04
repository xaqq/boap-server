/* 
 * File:   ResourceCollectorEntity.hpp
 * Author: xaqq
 *
 * Created on December 3, 2013, 1:44 PM
 */

#ifndef RESOURCECOLLECTORENTITY_HPP
#define	RESOURCECOLLECTORENTITY_HPP

#include "world/MovableEntity.hpp"
#include "ResourceEntity.hpp"

class ResourceCollectorEntity : public MovableEntity
{
public:
  ResourceCollectorEntity(WorldFacade &world, std::shared_ptr<btCollisionShape> shape);
  ResourceCollectorEntity(const ResourceCollectorEntity& orig) = delete;
  virtual ~ResourceCollectorEntity();
  
  
  virtual  void update(Milliseconds ms);
private:
  std::weak_ptr<ResourceEntity> targetResource_;
  
  bool findNewTarget();
  Milliseconds searchCooldown_;
  Milliseconds collectCooldown_;

};

#endif	/* RESOURCECOLLECTORENTITY_HPP */

