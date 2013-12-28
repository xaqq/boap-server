/* 
 * File:   AreaInstance.hpp
 * Author: xaqq
 *
 * Created on December 22, 2013, 3:35 AM
 */

#ifndef DB_AREAINSTANCE_HPP
#define	DB_AREAINSTANCE_HPP


#include <memory>
#include <string>
#include <vector>
#include "odb/core.hxx"
#include "odb/lazy-ptr.hxx"
#include "Area.hpp"

namespace DB
{
#pragma db object pointer(std::shared_ptr)

    /**
     * An instance of an Area (Database entry). Each GameObject entry can be in at most one AreaInstance.
     * When an instance of an Area is created, it runs in its own thread and instanciate all game object
     * that are needed for this area.
     */
    class AreaInstance
    {
    public:
        /**
         * A lazy collection of game object.
         */
        typedef std::vector<odb::lazy_shared_ptr<class GameObject >> GOList;

        const std::string &uuid() const
        {
            return uuid_;
        }

        void uuid(const std::string &uid)
        {
            uuid_ = uid;
        }

        std::shared_ptr<Area> areaTemplate()
        {
            return areaTemplate_;
        }

        void areaTemplate(std::shared_ptr<Area> tpl)
        {
            areaTemplate_ = tpl;
        }
        
        void addGameObject(std::shared_ptr<GameObject> go)
        {
            gameObjects_.push_back(go);
        }
        
    private:
        friend class odb::access;

#pragma db id 
        /**
         * This is the Primary Key. It identifies a unique Area instance.
         */
        std::string uuid_;

        /**
         * The Area object that is the template of this instance.
         */
        std::shared_ptr<Area> areaTemplate_;
    public:
        /**
         * List of game object.
         */
#pragma db null
        GOList gameObjects_;
    };
#pragma db object(AreaInstance)

}


#ifdef ODB_COMPILER
 #include "GameObject.hpp"
#endif

#endif	/* DB_AREAINSTANCE_HPP */

