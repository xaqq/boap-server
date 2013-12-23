/* 
 * File:   GameObject.hpp
 * Author: xaqq
 *
 * Created on December 21, 2013, 11:46 PM
 */

#ifndef GAMEOBJECT_HPP
#define	GAMEOBJECT_HPP


#include <memory>
#include <string>
#include "odb/core.hxx"

#include "StatSheet.hpp"
#include "GeometryObject.hpp"
#include "GameObjectTemplate.hpp"

namespace DB
{
#pragma db object pointer(std::shared_ptr)

    /**
     * A GameObject entry.
     */
    class GameObject
    {
    public:

        GameObject() :
        xPos_(0),
        yPos_(0),
        zPos_(0),
        xAngle_(0),
        yAngle_(0),
        zAngle_(0)
        {
        };

        virtual ~GameObject()
        {
        }

        void stats(std::shared_ptr<StatSheet> stats)
        {
            stats_ = stats;
        }

        std::shared_ptr<StatSheet> stats() const
        {
            return stats_;
        }

        void name(const std::string &name)
        {
            name_ = name;
        }

        std::string name() const
        {
            return name_;
        }

        void level(int level_)
        {
            this->level_ = level_;
        }

        int level() const
        {
            return level_;
        }

        const std::string &uuid() const
        {
            return uuid_;
        }

        std::shared_ptr<GameObjectTemplate> goTemplate()
        {
            return goTemplate_;
        }

    protected:
        friend class odb::access;

#pragma db id 
        /**
         * This is the Primary Key of the GameObject relation. It's the uuid of the GO.
         */
        std::string uuid_;

        /**
         * The level of the game object
         */
        int level_;

        /**
         * The display name of the game object. It defaults to its template name.
         * 
         * However, this field is useful for player character name.
         */
        std::string name_;

        /**
         * Stats for this game object. It default to a copy of the template's one;
         */
        std::shared_ptr<StatSheet> stats_;

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
         * The Area instance this game object is in
         */
#pragma db inverse(gameObjects_)
        std::weak_ptr<class AreaInstance> area_;
    };
#pragma db object(DB::GameObject) polymorphic
}

#ifdef ODB_COMPILER
 #include "AreaInstance.hpp"
#endif

#endif	/* GAMEOBJECT_HPP */

