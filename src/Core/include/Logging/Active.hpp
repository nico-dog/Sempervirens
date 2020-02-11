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
#include <Logging/ActiveQueue.hpp>
//#include <functional>
//#include <memory>
//#include <thread>

namespace sempervirens::core::logging {

  class Active {

    using Message_t = std::function<void()>;
    
    class ActiveImpl;
    std::unique_ptr<ActiveImpl, void(*)(ActiveImpl*)> _pImpl;

  public:
    Active();
    ~Active();

    Active(Active const&) = delete;
    Active& operator=(Active const&) = delete;

    void send(Message_t msg);
  };
}
#endif
