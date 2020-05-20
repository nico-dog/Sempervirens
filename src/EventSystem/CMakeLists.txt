project(eventsystem VERSION 1.0 LANGUAGES CXX)

# Define target
add_library(eventsystem OBJECT)
target_sources(eventsystem PRIVATE Event.cpp)


target_precompile_headers(eventsystem PRIVATE ../../include/Sempervirens_pch.hpp)

# Set target include directories
target_include_directories(eventsystem PUBLIC ../../include)

# Set target compile options
target_compile_options(eventsystem PRIVATE -Wall -O2 -fPIC)


# Set target compile features
target_compile_features(eventsystem PRIVATE cxx_std_17)


# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(eventsystem PRIVATE PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_testing})
target_compile_definitions(eventsystem PRIVATE BUILD_UNITTESTING=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(eventsystem PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(eventsystem PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()



