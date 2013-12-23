/* 
 * File:   GeometryObject.hpp
 * Author: xaqq
 *
 * Created on December 19, 2013, 8:33 PM
 */

#ifndef GEOMETRYOBJECT_HPP
#define	GEOMETRYOBJECT_HPP


#include <memory>
#include <string>
#include <array>
#include "odb/core.hxx"
#include "GeometryVisitor.hpp"

namespace DB
{
#pragma db object pointer(std::shared_ptr)

/**
     * Object of this class are a persistent representation of a GeometryObject.
     * 
     * A GeometryObject is a wrapper around a Bullet CollisionObject, with a few application specific
     * data.
     * 
     * A GameObject can have at most one GeometryObject as their collider.
     * 
     * The visitor pattern is used for this class hierarchy. A GeometryVisitor object can visit
     * any GeometryObject. This double-dispatch stuff is usefull to isolate the data model (this class)
     * from in-game, Bullet dependant geometry object.
     */
    class GeometryObject
    {
    public:

        GeometryObject() : xDistance_(0), yDistance_(0), zDistance_(0),
        xAngle_(0), yAngle_(0), zAngle_(0),
        description_("Default description")
        {
        };

        virtual ~GeometryObject()
        {
        }

        /**
         * Method to implement visitor pattern.
         */
        virtual void accept(GeometryVisitor *v)
        {
            v->visit(this);
        }

        void description(const std::string &description)
        {
            description_ = description;
        }

        const std::string &description() const
        {
            return description_;
        }

        unsigned long id() const
        {
            return id_;
        }

        std::array<float, 3> relativeDistance() const
        {
            return std::array<float, 3>({xDistance_, yDistance_, zDistance_});
        }

        void relativeDistance(const std::array<float, 3> &dst)
        {
            xDistance_ = dst[0];
            yDistance_ = dst[1];
            zDistance_ = dst[2];
        }

        std::array<float, 3> angles() const
        {
            return std::array<float, 3>({xAngle_, yAngle_, zAngle_});
        }

        void angles(const std::array<float, 3> &angles)
        {
            xAngle_ = angles[0];
            yAngle_ = angles[1];
            zAngle_ = angles[2];
        }


    protected:
        friend class odb::access;

        /**
         * Just a description of what this GeometryObject is.
         */
        std::string description_;

        /**
         * Relative x-distance from the entity
         */
        float xDistance_;
        /**
         * Relative y-distance from the entity
         */
        float yDistance_;
        /**
         * Relative z-distance from the entity.
         */
        float zDistance_;

        /**
         * Default x-angle of the object.
         */
        float xAngle_;
        /**
         * Default y-angle of the object.
         */
        float yAngle_;
        /**
         * Default z-angle of the object.
         */
        float zAngle_;

#pragma db id auto 
        unsigned long id_;
    };
#pragma db object(GeometryObject) polymorphic
};

#endif	/* GAMEOBJECT_HPP */
