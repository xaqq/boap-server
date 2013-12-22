/* 
 * File:   ATask.cpp
 * Author: xaqq
 * 
 * Created on December 21, 2013, 7:33 PM
 */

#include "ATask.hpp"
#include "Log.hpp"
#include "Scheduler.hpp"

ATask::ATask()
{
}

ATask::~ATask()
{
}

void ATask::schedule(Thread t)
{
    switch (t)
    {
        case Thread::MAIN:
            Scheduler::instance()->runInServerThread(std::bind(&ATask::operator(), shared_from_this()));
            break;
        case Thread::TCP:
            Scheduler::instance()->runInTcpThread(std::bind(&ATask::operator(), shared_from_this()));
            break;
        case Thread::UDP:
            Scheduler::instance()->runInUdpThread(std::bind(&ATask::operator(), shared_from_this()));
            break;
        case Thread::HELPER:
            Scheduler::instance()->runInHelper(std::bind(&ATask::operator(), shared_from_this()));
            break;
        default:
            WARN("Task not scheduled because target thread is not handled.");
            break;
    }

}