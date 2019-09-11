project(lib VERSION 0.1 LANGUAGES CXX)

#***************************************
#
# define target src/includes
#
#***************************************
add_library(doglib SHARED
  src/utils/Active.cpp
  src/utils/Logger.cpp
  src/utils/LogMsg.cpp
  src/utils/LogLevel.cpp
  src/utils/LogSink.cpp)

target_include_directories(doglib
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

#***************************************
#
# set target compile options
#
#***************************************
target_compile_options(doglib
  PRIVATE
  -Wall -O2)

#***************************************
#
# set target compile features
#
#***************************************
target_compile_features(doglib
  PRIVATE
  cxx_std_17)

#***************************************
#
# set target compile definitions
#
#***************************************
# platform macros
if(UNIX)
target_compile_definitions(doglib
  PRIVATE LINUX=1)
endif()

# product macros
if(${--build_unit_test})
target_compile_definitions(doglib
  PRIVATE UNITTEST_BUILD=1)
endif()

# feature macros
if(${--feature_thread_affinity})
target_compile_definitions(doglib
  PRIVATE THREAD_AFFINITY=1)
endif()

#***************************************
#
# link to imported targets
#
#***************************************
target_link_libraries(doglib
  PUBLIC
  pthread)

#***************************************
#
# set target compile definitions
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
# define tests for CTest
#
#***************************************
add_executable(logger
  test/LoggerTest.cpp)
target_link_libraries(logger
  doglib)
add_test(NAME logger-test COMMAND logger)
