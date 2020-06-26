project(keyboard VERSION 1.0 LANGUAGES CXX)

# Define target
add_library(keyboard OBJECT)
if(UNIX)
target_sources(keyboard PRIVATE
  Platform/Linux/LinuxKeyboard.cpp)
endif()

target_precompile_headers(keyboard PRIVATE ../../include/Sempervirens_pch.hpp)

# Set target include directories
target_include_directories(keyboard PUBLIC ../../include)

# Set target compile options
target_compile_options(keyboard PRIVATE -Wall -O2 -fPIC)

# Set target compile features
target_compile_features(keyboard PRIVATE cxx_std_17)

# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(keyboard PRIVATE PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_testing})
target_compile_definitions(keyboard PRIVATE BUILD_UNITTESTING=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(keyboard PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(keyboard PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()




if(UNIX)
#find_package(X11 REQUIRED)
target_link_libraries(keyboard PUBLIC X11::X11)
endif()




