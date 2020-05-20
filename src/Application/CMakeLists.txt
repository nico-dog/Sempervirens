project(app VERSION 1.0 LANGUAGES CXX)

# Define target
add_library(app OBJECT)
target_sources(app PRIVATE Application.cpp)
target_include_directories(app PUBLIC ../../include)

target_precompile_headers(app PRIVATE ../../include/Sempervirens_pch.hpp)

# Set target compile options
target_compile_options(app PRIVATE -Wall -O2 -fPIC)

# Set target compile features
target_compile_features(app PRIVATE cxx_std_17)

# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(app PRIVATE PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_testing})
target_compile_definitions(app PRIVATE BUILD_UNITTESTING=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(app PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(app PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()


#target_link_libraries(app PUBLIC core window)


