project(graphics VERSION 1.0 LANGUAGES CXX)

#***************************************
#
# Define target
#
#***************************************
add_library(graphicsmgrlib STATIC
  src/GraphicsMgr/GraphicsMgr.cpp)

target_include_directories(graphicsmgrlib
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../App>)

add_library(graphicslib SHARED
  src/GraphicsRenderer/IGraphicsRenderer.cpp
  src/GraphicsRenderer/OpenGLRenderer.cpp)

target_include_directories(graphicslib
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../App>)
  
#***************************************
#
# Set target compile options
#
#***************************************
target_compile_options(graphicsmgrlib
  PRIVATE
  -Wall -O2)
  
target_compile_options(graphicslib
  PRIVATE
  -Wall -O2)
  
#***************************************
#
# Set target compile features
#
#***************************************
target_compile_features(graphicsmgrlib
  PUBLIC
  cxx_std_17)

target_compile_features(graphicslib
  PUBLIC
  cxx_std_17)
  
#***************************************
#
# Set target compile definitions
#
#***************************************
# platform macros
if(UNIX)
target_compile_definitions(graphicsmgrlib
  PUBLIC LINUX=1)
target_compile_definitions(graphicslib
  PUBLIC LINUX=1)  
endif()

# build macros
if(${build_unit_tests})
target_compile_definitions(graphicsmgrlib
  PUBLIC BUILD_UNITTESTS=1)
target_compile_definitions(graphicslib
  PUBLIC BUILD_UNITTESTS=1)  
message(STATUS "App is build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(graphicsmgrlib
  PUBLIC BUILD_LOGGING=1)
target_compile_definitions(graphicslib
  PUBLIC BUILD_LOGGING=1)  
message(STATUS "App is build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(graphicsmgrlib
  PUBLIC FEATURE_THREAD_AFFINITY=1)
target_compile_definitions(graphicslib
  PUBLIC FEATURE_THREAD_AFFINITY=1)  
endif()

#***************************************
#
# Link to imported targets
#
#***************************************
target_link_libraries(graphicsmgrlib
  PUBLIC
  utilitieslib)
  
target_link_libraries(graphicslib
  PUBLIC
  utilitieslib)

#  Threads::Threads)
#  pthread)

#***************************************
#
# Install
#
#***************************************
# 'make install' to the correct locations (provided by GNUInstallDirs)
#install(TARGETS graphicslib
#  EXPORT GraphicslibConfig
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
## RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
#install(EXPORT GraphicslibConfig DESTINATION share/Graphicslib/cmake)

# This makes the project importable from the build directory
#export(TARGETS graphicslib FILE GraphicslibConfig.cmake)

#***************************************
#
# Define tests for CTest
#
#***************************************
if(${build_unit_tests})
add_executable(graphicsmgr
  test/GraphicsMgrTest.cpp)
target_link_libraries(graphicsmgr
  graphicsmgrlib)
add_test(NAME graphicsmgr-test COMMAND graphicsmgr)
endif()
