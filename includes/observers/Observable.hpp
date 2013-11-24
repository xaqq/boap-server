/* 
 * File:   Observable.hpp
 * Author: xaqq
 *
 * Created on November 23, 2013, 9:39 PM
 */

#ifndef OBSERVABLE_HPP
#define	OBSERVABLE_HPP

#include <list>
#include <memory>

template<typename ObserverType>
class Observable
{
private:
  std::list<std::weak_ptr<ObserverType >> observers_;

public:

  void registerObserver(std::shared_ptr<ObserverType> observer)
  {
    observers_.push_back(observer);
  }

  void unregisterObserver(std::shared_ptr<ObserverType> observer)
  {
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
    for (auto o : observers_)
      {
        auto sptr = o.lock();
        if (sptr)
          c(sptr);
      }
  }
};


#endif	/* OBSERVABLE_HPP */

