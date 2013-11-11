/* 
 * File:   SafeQueue.hpp
 * Author: xaqq
 *
 * Created on November 4, 2013, 3:24 PM
 */

#ifndef SAFEQUEUE_HPP
#define	SAFEQUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeQueue
{
public:

  SafeQueue() { }
  SafeQueue(const SafeQueue& orig) = delete;

  virtual ~SafeQueue() { };
private:
  mutable std::mutex mutex_;
  std::queue<T> queue_;
  std::condition_variable cv_;

public:

  T pop()
  {
    std::unique_lock<std::mutex> lock(mutex_);

    while (queue_.empty())
      {
        cv_.wait(lock);
      }

    T value = std::move(queue_.front());
    queue_.pop();
    return value;
  }

  bool tryPop(T &target)
  {
    std::unique_lock<std::mutex> lock(mutex_);
    if (queue_.empty())
      return false;
    target = std::move(queue_.front());
    queue_.pop();
    return true;
  }

  void push(const T &object)
  {
    std::lock_guard<std::mutex> guard(mutex_);
    queue_.push(object);
  }

  void push(T &&object)
  {
    std::lock_guard<std::mutex> guard(mutex_);
    queue_.push(std::move(object));
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> guard(mutex_);
    return queue_.empty();
  }



};

#endif	/* SAFEQUEUE_HPP */

