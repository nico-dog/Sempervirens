cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(Sempervirens VERSION 1.0 LANGUAGES C CXX)

#***************************************
#
# To install libraries into proper locations on all platforms
#
#***************************************
include(GNUInstallDirs) 

#***************************************
#
# Import targets here
#
#***************************************
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#***************************************
#
# CTest
#
#***************************************
enable_testing()

#***************************************
#
# Project tree
#
#***************************************
add_subdirectory(lib)
#add_subdirectory(app)

