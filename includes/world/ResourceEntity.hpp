/* 
 * File:   ResourceEntity.hpp
 * Author: xaqq
 *
 * Created on December 3, 2013, 1:34 PM
 */

#ifndef RESOURCEENTITY_HPP
#define	RESOURCEENTITY_HPP

#include "world/GameEntity.hpp"

class ResourceEntity : public GameEntity
{
public:
  ResourceEntity(WorldFacade &world, std::shared_ptr<btCollisionShape> shape);
  ResourceEntity(const ResourceEntity& orig) = delete;
  virtual ~ResourceEntity();
  
  int quantity() const;

  /**
   * Try to collect qt unit of the resource;
   * collector is the gamentity who collect this resource;
   * @return quantity collected;
   */
  int collect(std::shared_ptr<GameEntity> collector, int qt);
private:
  int quantity_;

};

#endif	/* RESOURCEENTITY_HPP */

