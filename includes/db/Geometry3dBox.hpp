/* 
 * File:   Geometry3dBox.hpp
 * Author: xaqq
 *
 * Created on December 19, 2013, 9:27 PM
 */

#ifndef GEOMETRY3DBOX_HPP
#define	GEOMETRY3DBOX_HPP

#include <memory>
#include "odb/core.hxx"
#include "GeometryObject.hpp"
#include "GeometryVisitor.hpp"

namespace DB
{
/**
 * A GeometryObject that represents a 3d box (wrapper around a btBoxShape) with parameters (like
 * half-extends) stored in database.
 */
class Geometry3dBox : public GeometryObject {
public:

    Geometry3dBox() : xHalfExtend_(0),
    yHalfExtend_(0), zHalfExtend_(0) {
    }
    virtual void accept(GeometryVisitor *v)
    {
        v->visit(this);
    }    

    float xHalfExtend() const {
        return xHalfExtend_;
    }

    float yHalfExtend() const {
        return yHalfExtend_;
    }

    float zHalfExtend() const {
        return zHalfExtend_;
    }
    
    void halfExtends(const std::array<float, 3> &he)    
    {
        xHalfExtend_ = he[0];
        yHalfExtend_ = he[1];
        zHalfExtend_ = he[2];
    }
    
private:
    friend class odb::access;
    /**
     * The half x-size of the box
     */
    float xHalfExtend_;
    /**
     * The half y-size of the box
     */
    float yHalfExtend_;
    /**
     * The half z-size of the box
     */
    float zHalfExtend_;

};
#pragma db object(Geometry3dBox)
};


#endif	/* GEOMETRY3DBOX_HPP */

