/* 
 * File:   PlayerEntity.hpp
 * Author: xaqq
 *
 * Created on November 22, 2013, 7:20 AM
 */

#ifndef PLAYERENTITY_HPP
#define	PLAYERENTITY_HPP

#include "GameEntity.hpp"


class PlayerEntity : public GameEntity
{
  private:
    /**
     * The client who owns this entity.
     * This is a weak_ptr because the client obect could die (if the client get disconnected).
     */
    std::weak_ptr<AClient> client_;

    /**
     * The ID of the client; This could be useful for reconnecting someone.
     */
    std::size_t clientId_;
    
public:
  PlayerEntity();
  PlayerEntity(const PlayerEntity& orig);
  virtual ~PlayerEntity();
  
  
private:

};

#endif	/* PLAYERENTITY_HPP */

