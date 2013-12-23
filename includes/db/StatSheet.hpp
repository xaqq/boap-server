/* 
 * File:   StatSheet.hpp
 * Author: xaqq
 *
 * Created on December 19, 2013, 7:10 PM
 */

#ifndef STATSHEET_HPP
#define	STATSHEET_HPP

#include <memory>
#include <string>
#include "odb/core.hxx"

namespace DB
{
#pragma db object pointer(std::shared_ptr)
/**
 * A GameObject stat sheet.
 * 
 * This is used by GameObjectTemplate for the baseStat_ attribute.
 * Also, GameObject instances (all object in all AreaInstance) each have a StatSheet attribute
 * that represent their current base stats (update on level-up ?).
 */
class StatSheet
    {
    public:
        StatSheet() {};

        virtual ~StatSheet()
        {
        }

        int health() const
        {
            return health_;
        }

        void health(int h)
        {
            health_ = h;
        }

        int mana() const
        {
            return mana_;
        }

        void mana(int m)
        {
            mana_ = m;
        }

        float moveSpeed() const
        {
            return moveSpeed_;
        }

        float moveSpeed(float ms)
        {
            moveSpeed_ = ms;
        }

    private:
        friend class odb::access;

#pragma db id auto 
        unsigned long id_;
        int health_;
        int mana_;
        float moveSpeed_;
    };
#pragma db object(StatSheet)
}

#endif	/* STATSHEET_HPP */

