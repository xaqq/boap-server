/* 
 * File:   GameObject.hpp
 * Author: xaqq
 *
 * Created on December 28, 2013, 2:12 AM
 */

#ifndef GAMEOBJECT_HPP
#define	GAMEOBJECT_HPP

#include "db/DAO.hpp"
#include "Uuid.hpp"

/**
 * GameObject base class.
 * Anything in the world is a GameObject. A wall, a unit, a spell, etc
 */
class GameObject
{
public:
    typedef std::shared_ptr<GameObject> Ptr;
    GameObject(DB::GameObjectTemplatePtr goTemplate);
    GameObject(const GameObject&) = delete;
    virtual ~GameObject();

    const Uuid &uuid() const
    {
        return uuid_;
    }

    /**
     * Return the database object that represent this object
     */
    DB::GameObjectPtr dbData()
    {
        return dbData_;
    }

    /**
     * Remove this GameObject (and associated stuff) from the database.
     */
    virtual bool erase();
    
    virtual bool save();

private:
    Uuid uuid_;
    /**
     * Database representation of this GameObject.
     */
    DB::GameObjectPtr dbData_;
};

#endif	/* GAMEOBJECT_HPP */

