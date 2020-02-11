#define DYNAMICLIBS_UNIX_HPP
#include <DynamicLibs/DynamicLibs.hpp>
#include <Logging/Logger.hpp>
#include <dlfcn.h>

namespace sempervirens::core::dlibs {

  std::optional<dlib_t> load(std::string libname) {

    auto lib = dlopen(std::move(libname).c_str(), RTLD_LAZY);         
    if (!lib) {

      SEMPERVIRENS_ERR(dlerror());
      return std::nullopt;
    }
    return lib;
  }
  
  void release(dlib_t lib) {

    dlclose(lib);
  }
  
  std::optional<symb_t> getSymbol(dlib_t lib, std::string symbol) {

    auto symb = dlsym(lib, std::move(symbol).c_str());
    if (!symb) {

      SEMPERVIRENS_ERR(dlerror());
      return std::nullopt;
    }
    return symb;
  }
}
