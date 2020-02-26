cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Sempervirens VERSION 1.0 LANGUAGES C CXX)


set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

# To install libraries into proper locations on all platforms
include(GNUInstallDirs) 


# Imported targets
if(UNIX)
find_package(X11 REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
endif()


# CTest
enable_testing()


# Project tree
add_subdirectory(Vendors)
add_subdirectory(Core)
add_subdirectory(Window)
#add_subdirectory(Input)
#add_subdirectory(Renderer)
add_subdirectory(Application)


#######################################################
#
# Define target for sempervirens shared library
#
#######################################################

add_library(sempervirens SHARED)
target_sources(sempervirens PRIVATE $<TARGET_OBJECTS:core> $<TARGET_OBJECTS:window> $<TARGET_OBJECTS:app>)
target_link_libraries(sempervirens PRIVATE
  Threads::Threads
  X11::X11)




