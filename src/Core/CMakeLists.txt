project(core VERSION 1.0 LANGUAGES CXX)

# Define target
#add_library(core STATIC)
add_library(core OBJECT)
target_sources(core PRIVATE
  src/Logging/Active.cpp
  src/Logging/Logger.cpp
  src/Logging/LogMsg.cpp
  src/Logging/LogLevel.cpp
  src/Logging/LogSink.cpp
  src/UnitTesting/UnitTest.cpp
  src/UnitTesting/UnitTestRegister.cpp
  src/MemoryAlloc/MemoryArea.cpp
  src/MemoryAlloc/LinearAllocator.cpp)
if(UNIX)
target_sources(core PRIVATE
  src/MemoryAlloc/MemoryAlloc_unix.cpp)
endif()

target_precompile_headers(core PRIVATE ../Sempervirens_pch.hpp)

# Set target include directories
target_include_directories(core PUBLIC
  include
  ../Misc)


# Set target compile options
target_compile_options(core PRIVATE -Wall -O2 -fPIC)


# Set target compile features
target_compile_features(core PRIVATE cxx_std_17)


# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(core PRIVATE PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_testing})
target_compile_definitions(core PRIVATE BUILD_UNITTESTING=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(core PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(core PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()


# Link to imported targets
target_link_libraries(core PRIVATE Threads::Threads)


# Define tests
# NOTE: need to regenerate precompile headers at least for first target,
# cannot reuse from core because of different compile options/definitions/flags.
if(${build_unit_testing})

add_executable(logger)
target_sources(logger PRIVATE test/LoggerTest.cpp)
target_precompile_headers(logger PRIVATE ../Sempervirens_pch.hpp)
target_link_libraries(logger PRIVATE core)
target_compile_options(logger PRIVATE -Wall -O2 -fPIC)
target_compile_features(logger PRIVATE cxx_std_17)
target_compile_definitions(logger PRIVATE BUILD_UNITTESTING=1)
if(${build_logging})
target_compile_definitions(logger PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME logger-test COMMAND logger)

add_executable(register)
target_sources(register PRIVATE test/UnitTestRegisterTest.cpp)
target_precompile_headers(register REUSE_FROM logger)
target_link_libraries(register PRIVATE core)
target_compile_options(register PRIVATE -Wall -O2 -fPIC)
target_compile_features(register PRIVATE cxx_std_17)
target_compile_definitions(register PRIVATE BUILD_UNITTESTING=1)
if(${build_logging})
target_compile_definitions(register PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME register-test COMMAND register)

add_executable(arena)
target_sources(arena PRIVATE test/MemoryArenaTest.cpp)
target_precompile_headers(arena REUSE_FROM logger)
target_link_libraries(arena PRIVATE core)
target_compile_options(arena PRIVATE -Wall -O2 -fPIC)
target_compile_features(arena PRIVATE cxx_std_17)
target_compile_definitions(arena PRIVATE BUILD_UNITTESTING=1)
if(${build_logging})
target_compile_definitions(arena PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME arena-test COMMAND arena)

endif()
