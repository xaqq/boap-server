/* 
 * File:   Geometry2dBox.hpp
 * Author: xaqq
 *
 * Created on December 19, 2013, 9:27 PM
 */
#ifndef GEOMETRY2DBOX_HPP
#define GEOMETRY2DBOX_HPP

#include <memory>
#include "odb/core.hxx"
#include "GeometryObject.hpp"
#include "GeometryVisitor.hpp"

namespace DB
{

#pragma db object pointer(std::shared_ptr)
    /**
     * A GeometryObject that represents a 2box on the X-Y axis by default.
     * If you want a floor like object, this should be rotated 90 degrees on X.
     */
    class Geometry2dBox : public GeometryObject
    {
    public:

        Geometry2dBox() : xHalfExtend_(0),
        yHalfExtend_(0)
        {
        }

        virtual void accept(GeometryVisitor *v)
        {
            v->visit(this);
        }

        float xHalfExtend() const
        {
            return xHalfExtend_;
        }

        float yHalfExtend() const
        {
            return yHalfExtend_;
        }

        void halfExtends(const std::array<float, 2> &he)
        {
            xHalfExtend_ = he[0];
            yHalfExtend_ = he[1];
        }

    private:
        friend class odb::access;
        friend void insert_data();
        /**
         * The half x-size of the box
         */
        float xHalfExtend_;
        /**
         * The half y-size of the box
         */
        float yHalfExtend_;

    };

#pragma db object(Geometry2dBox) polymorphic
}
#endif