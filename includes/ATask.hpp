/* 
 * File:   ATask.hpp
 * Author: xaqq
 *
 * Created on December 21, 2013, 7:33 PM
 */

#ifndef ATASK_HPP
#define	ATASK_HPP

#include "Clock.hpp"
#include <memory>

class ATask : public std::enable_shared_from_this<ATask>
{
public:
    ATask();
    ATask(const ATask&) = delete;
    virtual ~ATask();

    enum Thread
    {
        THIS,
        MAIN,
        TCP,
        UDP,
        HELPER
    };

    void schedule(Thread t = Thread::THIS);
    //  void schedule(Thread t, Milliseconds delay);

    virtual void operator()() = 0;
private:

};

#endif	/* ATASK_HPP */

