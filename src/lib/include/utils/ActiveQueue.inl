#ifndef ACTIVEQUEUE_INL
#define ACTIVEQUEUE_INL

namespace dog::utils {
  
  template <typename T>
  void ActiveQueue<T>::pop(T& msg) {

    lock_t lock{_mutex};
    while (_q.empty()) 
      _ready.wait(lock);

    msg = std::move(_q.front());
    _q.pop_front();
  }
  
  template <typename T>
  void ActiveQueue<T>::push(T msg) {

    if (lock_t lock{_mutex}; true) _q.push_back(std::move(msg));
    _ready.notify_one();
  }
}
#endif
