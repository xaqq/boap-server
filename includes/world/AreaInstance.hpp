/* 
 * File:   AreaInstance.hpp
 * Author: xaqq
 *
 * Created on December 23, 2013, 5:33 AM
 */

#ifndef AREAINSTANCE_HPP
#define	AREAINSTANCE_HPP

#include <memory>
#include "Uuid.hpp"
#include "db/DAO.hpp"

namespace DB
{
    class AreaInstance;
};

/**
 * This class represents an instance of a given Area in the game server.
 */
class AreaInstance
{
public:
    /**
     * Create a new AreaInstance, using the area parameter as the template for the instance.
     * From the area parameter, this instance will retrieve its default states and initialize itself.
     */
    AreaInstance(DB::AreaPtr area);
    /**
     * Construct a new AreaInstance and provide its database entry for loading.
     */
    AreaInstance(std::shared_ptr<DB::AreaInstance> dbData);

    AreaInstance(const AreaInstance&) = delete;
    virtual ~AreaInstance();

    
    /**
     * Erase this area instance. It will be deleted from the database.
     * Also erase all game object that are inside this instance
     */
    bool erase();
    
    void stop();
    
    const Uuid &uuid()
    {
        return uuid_;
    }
    
private:
    
    /**
     * List of gameobject in the instance.
     */
    std::list<std::shared_ptr<class GameObject>> gameObjects_;
    
    /**
     * Spawn the default game objects into the world.
     */
    bool spawnDefaultGameObjects();
    
    Uuid uuid_;
    std::shared_ptr<DB::AreaInstance> dbData_;

};

#endif	/* AREAINSTANCE_HPP */

