project(lib VERSION 0.1 LANGUAGES CXX)

#***************************************
#
# Define target
#
#***************************************
add_library(utilitieslib STATIC
  src/Logging/Active.cpp
  src/Logging/Logger.cpp
  src/Logging/LogMsg.cpp
  src/Logging/LogLevel.cpp
  src/Logging/LogSink.cpp
  src/UnitTesting/UnitTest.cpp
  src/UnitTesting/UnitTestRegister.cpp)

target_include_directories(utilitieslib
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include)
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include, ${CMAKE_CURRENT_SOURCE_DIR}/../App>)  
#  $<INSTALL_INTERFACE:include>)

message(STATUS "******** dir = ${CMAKE_CURRENT_SOURCE_DIR}")

#***************************************
#
# Set target compile options
#
#***************************************
target_compile_options(utilitieslib
  PRIVATE
  -Wall -O2)

#***************************************
#
# Set target compile features
#
#***************************************
target_compile_features(utilitieslib
  PUBLIC
  cxx_std_17)

#***************************************
#
# Set target compile definitions
#
#***************************************
# platform macros
if(UNIX)
target_compile_definitions(utilitieslib
  PUBLIC LINUX=1)
endif()

# build macros
if(${build_unit_tests})
target_compile_definitions(utilitieslib
  PUBLIC BUILD_UNITTESTS=1)
endif()
if(${build_logging})
target_compile_definitions(utilitieslib
  PUBLIC BUILD_LOGGING=1)
message(STATUS "set logging flag to ${build_logging}")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(utilitieslib
  PUBLIC FEATURE_THREAD_AFFINITY=1)
endif()

#***************************************
#
# Link to imported targets
#
#***************************************
target_link_libraries(utilitieslib
  PUBLIC
  Threads::Threads)
#  pthread)

#***************************************
#
# Install
#
#***************************************
# 'make install' to the correct locations (provided by GNUInstallDirs)
#install(TARGETS utilitieslib
#  EXPORT UtilitieslibConfig
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
## RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
#install(EXPORT UtilitieslibConfig DESTINATION share/Utilitieslib/cmake)

# This makes the project importable from the build directory
#export(TARGETS utilitieslib FILE UtilitieslibConfig.cmake)

#***************************************
#
# Define tests for CTest
#
#***************************************
add_executable(logger
  test/LoggerTest.cpp)
target_link_libraries(logger
  utilitieslib)
add_test(NAME logger-test COMMAND logger)

add_executable(register
  test/UnitTestRegisterTest.cpp)
target_link_libraries(register
  utilitieslib)
add_test(NAME register-test COMMAND register)
