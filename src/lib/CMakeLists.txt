project(lib VERSION 0.1 LANGUAGES CXX)

#***************************************
#
# Define target src/includes
#
#***************************************
add_library(doglib SHARED
  src/utils/Active.cpp
  src/utils/Logger.cpp
  src/utils/LogMsg.cpp
  src/utils/LogLevel.cpp
  src/utils/LogSink.cpp
  src/utils/UnitTest.cpp
  src/utils/UnitTestRegister.cpp)

target_include_directories(doglib
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
#  $<INSTALL_INTERFACE:include>)

#***************************************
#
# Set target compile options
#
#***************************************
target_compile_options(doglib
  PRIVATE
  -Wall -O2)

#***************************************
#
# Set target compile features
#
#***************************************
target_compile_features(doglib
  PUBLIC
  cxx_std_17)

#***************************************
#
# Set target compile definitions
#
#***************************************
# platform macros
if(UNIX)
target_compile_definitions(doglib
  PUBLIC LINUX=1)
endif()

# build macros
if(${build_unit_tests})
target_compile_definitions(doglib
  PUBLIC BUILD_UNITTESTS=1)
endif()
if(${build_logging})
target_compile_definitions(doglib
  PUBLIC BUILD_LOGGING=1)
message(STATUS "set logging flag to ${build_logging}")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(doglib
  PUBLIC FEATURE_THREAD_AFFINITY=1)
endif()

#***************************************
#
# Link to imported targets
#
#***************************************
target_link_libraries(doglib
  PUBLIC
  Threads::Threads)
#  pthread)

#***************************************
#
# Install
#
#***************************************
# 'make install' to the correct locations (provided by GNUInstallDirs)
#install(TARGETS doglib
#  EXPORT DoGLibConfig
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
## RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
#install(EXPORT DoGLibConfig DESTINATION share/DoGLib/cmake)

# This makes the project importable from the build directory
#export(TARGETS doglib FILE DoGLibConfig.cmake)

#***************************************
#
# Define tests for CTest
#
#***************************************
add_executable(logger
  test/LoggerTest.cpp)
target_link_libraries(logger
  doglib)
add_test(NAME logger-test COMMAND logger)

add_executable(register
  test/UnitTestRegisterTest.cpp)
target_link_libraries(register
  doglib)
add_test(NAME register-test COMMAND register)
