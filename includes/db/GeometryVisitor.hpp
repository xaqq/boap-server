/* 
 * File:   GeometryVisitor.hpp
 * Author: xaqq
 *
 * Created on December 21, 2013, 10:04 PM
 */

#ifndef GEOMETRYVISITOR_HPP
#define	GEOMETRYVISITOR_HPP

namespace DB
{
/**
 * A base class to visit the GeometryObject hierarchy.
 */
class GeometryVisitor
{
public:
    virtual ~GeometryVisitor() {}

    virtual void visit(class GeometryObject *o)
    {
    }

    virtual void visit(class Geometry3dBox *b)
    {
    }

    virtual void visit(class Geometry2dBox *b)
    {
    }

    virtual void visit(class GeometrySphere *b)
    {
    }
};
};

#endif	/* GEOMETRYVISITOR_HPP */

