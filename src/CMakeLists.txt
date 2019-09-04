cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(UDMX VERSION 0.1 LANGUAGES C CXX)

include(GNUInstallDirs) # To install libraries into proper locations on all platforms

set(CMAKE_CXX_STANDARD 17) # To replace extra -std=gnu++11 that overtakes target_compile_options with -std=gnu++1z

# Here import targets

enable_testing()

add_subdirectory(lib)
add_subdirectory(app)
