project(logging VERSION 1.0 LANGUAGES CXX)

# Define target
add_library(logging OBJECT)
target_sources(logging PRIVATE
  Logger.cpp
  ConsoleLogger.cpp)


target_precompile_headers(logging PRIVATE ../../include/Sempervirens_pch.hpp)

# Set target include directories
target_include_directories(logging PUBLIC ../../include)


# Set target compile options
target_compile_options(logging PRIVATE -Wall -O2 -fPIC)


# Set target compile features
target_compile_features(logging PRIVATE cxx_std_17)


# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(logging PRIVATE PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_testing})
target_compile_definitions(logging PRIVATE BUILD_UNITTESTING=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(logging PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(logging PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()


# Link to imported targets
#target_link_libraries(logging PRIVATE Threads::Threads)



if(${build_unit_testing})

add_executable(logger)
target_sources(logger PRIVATE ../../tests/Logging/LoggerTest.cpp)
target_precompile_headers(logger PRIVATE ../../include/Sempervirens_pch.hpp)
target_link_libraries(logger PRIVATE unittesting logging)
target_compile_options(logger PRIVATE -Wall -O2 -fPIC)
target_compile_features(logger PRIVATE cxx_std_17)
target_compile_definitions(logger PRIVATE BUILD_UNITTESTING=1)
if(${build_logging})
target_compile_definitions(logger PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME logger-test COMMAND logger)

endif()
