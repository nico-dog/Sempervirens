project(utilities VERSION 1.0 LANGUAGES CXX)

# Define target
add_library(utilities STATIC)
target_sources(utilities PRIVATE
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
target_sources(utilities PRIVATE
  ../App/src/MemoryAlloc/MemoryAlloc_unix.cpp)
endif()


# Set target include directories
target_include_directories(utilities PUBLIC
  include
  ../App/include)


# Set target compile options
target_compile_options(utilities PRIVATE -Wall -O2 -fPIC)


# Set target compile features
target_compile_features(utilities PRIVATE cxx_std_17)


# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(utilities PRIVATE PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_tests})
target_compile_definitions(utilities PRIVATE BUILD_UNITTESTS=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(utilities PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(utilities PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()


# Link to imported targets
target_link_libraries(utilities PRIVATE Threads::Threads)


# Install
# 'make install' to the correct locations (provided by GNUInstallDirs)
#install(TARGETS utilities
#  EXPORT UtilitiesConfig
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
## RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
#install(EXPORT UtilitiesConfig DESTINATION share/Utilities/cmake)

# This makes the project importable from the build directory
#export(TARGETS utilities FILE UtilitiesConfig.cmake)


# Define tests 
if(${build_unit_tests})

add_executable(logger)
target_sources(logger PRIVATE test/LoggerTest.cpp)
target_link_libraries(logger PRIVATE utilities)
target_compile_options(logger PRIVATE -Wall -O2 -fPIC)
target_compile_features(logger PRIVATE cxx_std_17)
target_compile_definitions(logger PRIVATE BUILD_UNITTESTS=1)
if(${build_logging})
target_compile_definitions(logger PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME logger-test COMMAND logger)

add_executable(register)
target_sources(register PRIVATE test/UnitTestRegisterTest.cpp)
target_link_libraries(register PRIVATE utilities)
target_compile_options(register PRIVATE -Wall -O2 -fPIC)
target_compile_features(register PRIVATE cxx_std_17)
target_compile_definitions(register PRIVATE BUILD_UNITTESTS=1)
if(${build_logging})
target_compile_definitions(register PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME register-test COMMAND register)

add_executable(arena)
target_sources(arena PRIVATE test/MemoryArenaTest.cpp)
target_link_libraries(arena PRIVATE utilities)
target_compile_options(arena PRIVATE -Wall -O2 -fPIC)
target_compile_features(arena PRIVATE cxx_std_17)
target_compile_definitions(arena PRIVATE BUILD_UNITTESTS=1)
if(${build_logging})
target_compile_definitions(arena PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME arena-test COMMAND arena)

endif()
