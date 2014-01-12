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
#include "observers/Observable.hpp"
#include "behaviors/Behavior.hpp"

namespace DB
{
    class AreaInstance;
};

/**
 * This class represents an instance of a given Area in the game server.
 * The object is not yet initialized. You need to call the method init() before
 * calling run().
 * 
 * The init method will either load the instance from it's persisted state or create a new one.
 */
class AreaInstance : public Observable<class IAreaInstanceObserver>
{
public:

    AreaInstance()
    {
    }
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

    void processPacket();

    bool initialize();

    bool update();

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

    bool stopped() const
    {
        return !running_;
    }

private:
    bool running_;
    /**
     * List of gameobject in the instance.
     */
    std::list<std::shared_ptr<class GameObject >> gameObjects_;

    /**
     * Spawn the default game objects into the world.
     */
    bool spawnDefaultGameObjects();

    /**
     * Behavior that controll initialization, updating, and ending of the instance
     */
    Behavior behavior_;

    Uuid uuid_;
    std::shared_ptr<DB::AreaInstance> dbData_;

    /**
     * Cleanup when stopped
     */
    void cleanup();
    
};

#endif	/* AREAINSTANCE_HPP */

