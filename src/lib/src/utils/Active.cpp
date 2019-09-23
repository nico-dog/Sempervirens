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
    
    ~ActiveImpl() {

      _thd->join();
    }

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
  //Active::Active() {

  //  _thd = std::unique_ptr<std::thread>(new std::thread([=]{ this->run(); }));
  //}
  
  Active::~Active() {

    //send([&](){ std::cout << "Active dtor, sending done signal\n"; });
    send([&](){ _pImpl->_done = true; });

    //send([&](){ _done = true; });
    //_thd->join();
    //_pImpl->_thd->join();
    //gLog << "Active dtor, sent done signal";
  }

  void Active::send(Message_t msg) {

    _pImpl->_q.push(msg);
    //_q.push(msg);
  }

  /*
  void Active::run() {

    while (!_done)
    {
      Message_t msg;
      _q.pop(msg);
      msg();
    } 
  }
  */
}
