#define ACTIVE_CPP
#include <utils/Active.hpp>
#include <utils/ActiveQueue.hpp>
#include <thread>

namespace dog::utils {

  class Active::ActiveImpl {

  public:
    ActiveImpl() {

      _thd = std::unique_ptr<std::thread>(new std::thread([=]{ this->run(); }));
    }
    
    ~ActiveImpl() { _thd->join(); }

    void run() {
      while (!_done)
      {
	Message_t msg;
	_q.pop(msg);
	msg();
      } 
    }
    
    bool _done{false};
    std::unique_ptr<std::thread> _thd{nullptr};
    ActiveQueue<Message_t> _q;
  };

  Active::Active() : _pImpl{new ActiveImpl{}, [](ActiveImpl* ptr){ delete ptr; }} {}

  Active::~Active() {

    send([&](){ _pImpl->_done = true; });
  }

  void Active::send(Message_t msg) {

    _pImpl->_q.push(msg);
  }
}
