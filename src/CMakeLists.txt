cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(Sempervirens VERSION 0.1 LANGUAGES C CXX)

# To install libraries into proper locations on all platforms
include(GNUInstallDirs) 

# To replace extra -std=gnu++11 that overwrites target_compile_options with -std=gnu++1z
set(CMAKE_CXX_STANDARD 17) 

# Here import targets

enable_testing()

add_subdirectory(lib)
add_subdirectory(app)
