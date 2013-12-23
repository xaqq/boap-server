/* 
 * File:   GeometrySphere.hpp
 * Author: xaqq
 *
 * Created on December 19, 2013, 9:27 PM
 */

#ifndef GEOMETRYSPHERE_HPP
#define GEOMETRYSPHERE_HPP

#include <memory>
#include "odb/core.hxx"
#include "GeometryObject.hpp"
#include "GeometryVisitor.hpp"

namespace DB
{

    /**
     * A GeometryObject that represents a sphere
     */
    class GeometrySphere : public GeometryObject
    {
    public:

        GeometrySphere() : radius_(0)
        {
        }

        virtual void accept(GeometryVisitor *v)
        {
            v->visit(this);
        }

        float radius() const
        {
            return radius_;
        }
        
        void radius(float r)
        {
            radius_ = r;
        }

    private:
        friend class odb::access;
        friend void insert_data();

        /**
         * The radius of the sphere
         */
        float radius_;
    };
#pragma db object(GeometrySphere)
};

#endif
