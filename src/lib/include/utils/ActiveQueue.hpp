//***************************************************
//
// Definition of ActiveQueue object:
// An ActiveQueue is a simple thread-safe queue for an Active object.
// The queue is templated to handle different message types as defined by Active oject.
// Low-contention resource, does not implement non-blocking try_push/try_pop operations.
// Producer/consumer synchronization with condition variable.
//
//***************************************************
#ifndef ACTIVEQUEUE_HPP
#define ACTIVEQUEUE_HPP
#include <deque>
#include <mutex>
#include <condition_variable>

namespace dog::utils {

  template <typename T>
  class ActiveQueue {

    using lock_t = std::unique_lock<std::mutex>;
    
    std::deque<T> _q;
    std::mutex _mutex;
    std::condition_variable _ready;
    
  public:
    ActiveQueue() = default;
    void pop(T&);
    void push(T);
  };
}
#include <utils/ActiveQueue.inl>
#endif
