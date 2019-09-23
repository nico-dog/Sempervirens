//***************************************************
//
// Definition of Active object:
// An Active object is a resource held by a higher-level abstraction entity (i.e. Logger)
// which holds a private thread and queue to allow the owner to process messages asynchronously.
// Based on Herb Sutter's implementation.
//
//***************************************************
#ifndef ACTIVE_HPP
#define ACTIVE_HPP
#include <functional>
#include <memory>

#include <utils/ActiveQueue.hpp>
#include <thread>

namespace dog::utils {

  class Active {

    using Message_t = std::function<void()>;
    
    class ActiveImpl;
    std::unique_ptr<ActiveImpl, void(*)(ActiveImpl*)> _pImpl;

    //void run();

    //bool _done{false};
    //std::unique_ptr<std::thread> _thd{nullptr};
    //ActiveQueue<Message_t> _q;

  public:
    Active();
    ~Active();

    Active(Active const&) = delete;
    Active& operator=(Active const&) = delete;

    void send(Message_t msg);
  };
}
#endif
