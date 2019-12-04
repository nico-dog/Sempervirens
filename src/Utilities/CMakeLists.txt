project(utilities VERSION 1.0 LANGUAGES CXX)

#***************************************
#
# Define target
#
#***************************************
if(UNIX)
add_library(utilities STATIC
  src/Logging/Active.cpp
  src/Logging/Logger.cpp
  src/Logging/LogMsg.cpp
  src/Logging/LogLevel.cpp
  src/Logging/LogSink.cpp
  src/UnitTesting/UnitTest.cpp
  src/UnitTesting/UnitTestRegister.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../App/src/MemoryAlloc/MemoryAlloc_unix.cpp
  src/MemoryAlloc/MemoryArea.cpp
  src/MemoryAlloc/LinearAllocator.cpp)
endif()

target_include_directories(utilities
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../App/include>)  
#  $<INSTALL_INTERFACE:include>)

#***************************************
#
# Set target compile options
#
#***************************************
target_compile_options(utilities
  PRIVATE
  -Wall -O2 -fPIC)

#***************************************
#
# Set target compile features
#
#***************************************
target_compile_features(utilities
  PUBLIC
  cxx_std_17)

#***************************************
#
# Set target compile definitions
#
#***************************************
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(utilities
  PUBLIC PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_tests})
target_compile_definitions(utilities
  PUBLIC BUILD_UNITTESTS=1)
message(STATUS "App is build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(utilities
  PUBLIC BUILD_LOGGING=1)
message(STATUS "App is build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(utilities
  PUBLIC FEATURE_THREAD_AFFINITY=1)
endif()

#***************************************
#
# Link to imported targets
#
#***************************************
target_link_libraries(utilities
  PUBLIC
  Threads::Threads)
#  pthread)

#***************************************
#
# Install
#
#***************************************
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

#***************************************
#
# Define tests for CTest
#
#***************************************
if(${build_unit_tests})
add_executable(logger
  test/LoggerTest.cpp)
target_link_libraries(logger
  utilities)
add_test(NAME logger-test COMMAND logger)

add_executable(register
  test/UnitTestRegisterTest.cpp)
target_link_libraries(register
  utilities)
add_test(NAME register-test COMMAND register)

add_executable(arena
  test/MemoryArenaTest.cpp)
target_link_libraries(arena
  utilities)
add_test(NAME arena-test COMMAND arena)
endif()
