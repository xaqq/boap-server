/* 
 * File:   AreaInstance.hpp
 * Author: xaqq
 *
 * Created on December 22, 2013, 3:35 AM
 */

#ifndef AREAINSTANCE_HPP
#define	AREAINSTANCE_HPP


#include <memory>
#include <string>
#include <vector>
#include "odb/core.hxx"
#include "odb/lazy-ptr.hxx"
#include "Area.hpp"
#include "GameObject.hpp"

namespace DB
{
#pragma db object pointer(std::shared_ptr)

    /**
     * An instance of an Area. Each GameObject entry can be in at most one AreaInstance.
     * When an instance of an Area is created, it runs in its own thread and instanciate all game object
     * that are needed for this area.
     */
    class AreaInstance
    {
    public:
        /**
         * A lazy collection of game object.
         */
        typedef std::vector<odb::lazy_shared_ptr<GameObject >> GOList;

        const std::string &uuid() const
        {
            return uuid_;
        }

        std::shared_ptr<Area> areaTemplate()
        {
            return areaTemplate_;
        }
        
        void areaTemplate(std::shared_ptr<Area> tpl)
        {
            areaTemplate_ = tpl;
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

        /**
         * List of game object.
         */
#pragma db null
        GOList gameObjects_;
    };
#pragma db object(AreaInstance)

}
#endif	/* AREAINSTANCE_HPP */

