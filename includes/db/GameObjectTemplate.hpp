/* 
 * File:   GameObjectTemplate.hpp
 * Author: xaqq
 *
 * Created on December 19, 2013, 8:33 PM
 */

#ifndef GAMEOBJECTTEMPLATE_HPP
#define	GAMEOBJECTTEMPLATE_HPP


#include <memory>
#include <string>
#include "odb/core.hxx"

#include "StatSheet.hpp"
#include "GeometryObject.hpp"

namespace DB
{
#pragma db object pointer(std::shared_ptr)

    /**
     * A template for a GameObject instance. This describe the gameobject but leave out
     * data such as position, orientation and level, because those are instance specific. More than one
     * gameobject can share the same template.
     */
    class GameObjectTemplate
    {
    public:

        GameObjectTemplate()
        {
        };

        virtual ~GameObjectTemplate()
        {
        }

        void baseStats(std::shared_ptr<StatSheet> baseStats)
        {
            baseStats_ = baseStats;
        }

        std::shared_ptr<StatSheet> baseStats() const
        {
            return baseStats_;
        }

        void name(const std::string &name)
        {
            name_ = name;
        }

        std::string name() const
        {
            return name_;
        }

        void baseLevel(int baseLevel_)
        {
            this->baseLevel_ = baseLevel_;
        }

        int baseLevel() const
        {
            return baseLevel_;
        }

        unsigned long id() const
        {
            return id_;
        }

    private:
        friend class odb::access;

#pragma db id auto 
        /**
         * This is the Primary Key of the GameObjectTemplate relation.
         */
        unsigned long id_;

        /**
         * The base level of this game object. This value will be set as the GameObject's level
         * when it is spawned from the template.
         */
        int baseLevel_;
        /**
         * The display name of the game object.
         */
        std::string name_;

        /**
         * Base stats for this game object.
         */
        std::shared_ptr<StatSheet> baseStats_;

        /**
         * The geometry of this game object
         */
        std::shared_ptr<GeometryObject> geometry_;
    };
#pragma db object(DB::GameObjectTemplate)
}

#endif	/* GAMEOBJECT_HPP */

