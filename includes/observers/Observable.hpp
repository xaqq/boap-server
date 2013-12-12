/* 
 * File:   Observable.hpp
 * Author: xaqq
 *
 * Created on November 23, 2013, 9:39 PM
 */

#ifndef OBSERVABLE_HPP
#define	OBSERVABLE_HPP

#include <thread>
#include <list>
#include <memory>
#include "Log.hpp"


/**
 * Thread safe base class to be observable.
 */
template<typename ObserverType>
class Observable
{
private:
  std::list<std::weak_ptr<ObserverType >> observers_;
  mutable std::mutex mutex_;

public:

  void registerObserver(std::shared_ptr<ObserverType> observer)
  {
    std::lock_guard<std::mutex> guard(mutex_);
    observers_.push_back(observer);
  }

  void unregisterObserver(std::shared_ptr<ObserverType> observer)
  {
    std::lock_guard<std::mutex> guard(mutex_);
    std::weak_ptr<ObserverType> wptr = observer;
    observers_.remove(wptr);
  }

  /**
   * Dispatch the notification; EventCall should be a prepared callable that is a method
   * of the ObserverType class.
   * @param c
   */
  template<typename EventCall>
  void dispatch(EventCall c)
  {
    std::lock_guard<std::mutex> guard(mutex_);
    for (auto o : observers_)
      {
        auto sptr = o.lock();
        if (sptr)
          c(sptr);
        else
          WARN("Invalid weak ptr");
      }
  }
};


#endif	/* OBSERVABLE_HPP */

