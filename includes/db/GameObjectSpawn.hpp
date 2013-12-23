/* 
 * File:   GameObjectSpawn.hpp
 * Author: xaqq
 *
 * Created on December 22, 2013, 4:07 AM
 */

#ifndef GAMEOBJECTSPAWN_HPP
#define	GAMEOBJECTSPAWN_HPP



#include <memory>
#include <string>
#include "odb/core.hxx"
#include "GeometryObject.hpp"
#include "GameObjectTemplate.hpp"

namespace DB
{
#pragma db object pointer(std::shared_ptr)
    /**
     * A GameObjectSpawn entry. It has information about where to spawn initial game object
     * for an Area.
     */
    class GameObjectSpawn
    {
    public:

        GameObjectSpawn() :
        xPos_(0),
        yPos_(0),
        zPos_(0),
        xAngle_(0),
        yAngle_(0),
        zAngle_(0)
        {
        };

        virtual ~GameObjectSpawn()
        {
        }

        std::shared_ptr<GameObjectTemplate> goTemplate()
        {
            return goTemplate_;
        }

    protected:
        friend class odb::access;

#pragma db id auto
        /**
         * Id of the spawn info entry (pretty much useless)
         */
        unsigned long id_;
        /**
         * The geometry of this game object
         */
        std::shared_ptr<GameObjectTemplate> goTemplate_;

        /**
         * x-position in the world
         */
        float xPos_;
        /**
         * y-position in the world
         */
        float yPos_;
        /**
         * z-position in the world
         */
        float zPos_;

        /**
         * x-angle of the object.
         */
        float xAngle_;
        /**
         * y-angle of the object.
         */
        float yAngle_;
        /**
         * z-angle of the object.
         */
        float zAngle_;

        /**
         * The Area this entry is for
         */
        std::shared_ptr<class Area> area_;
    };
#pragma db object(GameObjectSpawn)
}

#ifdef ODB_COMPILER
 #include "Area.hpp"
#endif

#endif	/* GAMEOBJECTSPAWN_HPP */

