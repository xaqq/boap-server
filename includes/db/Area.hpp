/* 
 * File:   Area.hpp
 * Author: xaqq
 *
 * Created on December 21, 2013, 10:58 PM
 */

#ifndef AREA_HPP
#define	AREA_HPP

#include <memory>
#include <vector>
#include <string>
#include "odb/core.hxx"
#include "odb/lazy-ptr.hxx"

namespace DB
{
#pragma db object pointer(std::shared_ptr)

    /**
     * A database model class for an Area.
     * 
     * This class is used to create new instance of a given area.
     */
    class Area
    {
    public:
        /**
         * A collection of lazy weak pointer. That means that when a Area object is loaded,
         * all the spawn points for gameobject are not loaded yet.
         */
        typedef std::vector<odb::lazy_weak_ptr<class GameObjectSpawn >> LazyGameObjectSpawnVector;
        
        /**
         * Collection of GameObjectSpawn object
         */
        typedef std::vector<std::shared_ptr<GameObjectSpawn >> GameObjectSpawnVector;

        unsigned long id() const
        {
            return id_;
        }

        const std::string &name() const
        {
            return name_;
        }

        bool instanceRequired()
        {
            return instanceRequired_;
        }
        
        /**
         * Build a vector of GameObjectSpawn object.
         * This method can be costly, because it queries the database to load the collection.
         */
        GameObjectSpawnVector spawnData();

    public:
        friend class odb::access;

#pragma db id auto 
        unsigned long id_;

        /**
         * If this bool is set to true, that means that the server
         * is required to start up a new instance for this area if none exists.
         */
        bool instanceRequired_;

#pragma db unique\
                    type("VARCHAR(255)")
        std::string name_;

#pragma db inverse(area_)
        /**
         * Collection of Spawn information for GameObject in this Area.
         * This is lazy
         */
        LazyGameObjectSpawnVector goSpawnData_;
    };
    
#pragma db object(Area)
};

#ifdef ODB_COMPILER
#include "GameObjectSpawn.hpp"
#endif

#endif	/* AREA_HPP */

