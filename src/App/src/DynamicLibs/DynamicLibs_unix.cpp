#define DYNAMICLIBS_UNIX_HPP
#include <DynamicLibs/DynamicLibs.hpp>
#include <Logging/Logger.hpp>
#include <dlfcn.h>

namespace dog::app::dlibs {

  dlib_t load(std::string libname) {

    auto lib = dlopen(std::move(libname).c_str(), RTLD_LAZY);         
    if (!lib) {

      DOG_LOGERR(dlerror());
    }
    return lib;
  }
  
  void release(dlib_t lib) {

    dlclose(lib);
  }
  
  symb_t getSymbol(dlib_t lib, std::string symbol) {

    auto symb = dlsym(lib, std::move(symbol).c_str());
    if (!symb) {

      DOG_LOGERR(dlerror());
    }
    return symb;
  }
}
