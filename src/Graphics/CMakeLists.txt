project(graphics VERSION 1.0 LANGUAGES CXX)

#***************************************
#
# Define target
#
#***************************************
if(UNIX)
add_library(graphicsmgr STATIC
  src/GraphicsMgr/GraphicsMgr.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../App/src/DynamicLibs/DynamicLibs_unix.cpp
)
endif()

target_include_directories(graphicsmgr
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../App/include>)

add_library(graphicsogl SHARED
  src/GraphicsRenderer/IGraphicsRenderer.cpp
  src/GraphicsRenderer/OpenGLRenderer.cpp)

target_include_directories(graphicsogl
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../Utilities/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../App/include>)
  
#***************************************
#
# Set target compile options
#
#***************************************
target_compile_options(graphicsmgr
  PRIVATE
  -Wall -O2)
  
target_compile_options(graphicsogl
  PRIVATE
  -Wall -O2)
  
#***************************************
#
# Set target compile features
#
#***************************************
target_compile_features(graphicsmgr
  PUBLIC
  cxx_std_17)

target_compile_features(graphicsogl
  PUBLIC
  cxx_std_17)
  
#***************************************
#
# Set target compile definitions
#
#***************************************
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(graphicsmgr
  PUBLIC PLATFORM_UNIX=1)
target_compile_definitions(graphicsogl
  PUBLIC PLATFORM_UNIX=1)  
endif()

# build macros
if(${build_unit_tests})
target_compile_definitions(graphicsmgr
  PUBLIC BUILD_UNITTESTS=1)
target_compile_definitions(graphicsogl
  PUBLIC BUILD_UNITTESTS=1)  
message(STATUS "App is build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(graphicsmgr
  PUBLIC BUILD_LOGGING=1)
target_compile_definitions(graphicsogl
  PUBLIC BUILD_LOGGING=1)  
message(STATUS "App is build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(graphicsmgr
  PUBLIC FEATURE_THREAD_AFFINITY=1)
target_compile_definitions(graphicsogl
  PUBLIC FEATURE_THREAD_AFFINITY=1)  
endif()

#***************************************
#
# Link to imported targets
#
#***************************************
target_link_libraries(graphicsmgr
  PUBLIC
  ${CMAKE_DL_LIBS} # usually -ldl on unix platforms
  utilities)
  
target_link_libraries(graphicsogl
  PUBLIC
  utilities)

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
add_executable(graphics
  test/GraphicsMgrTest.cpp)
target_link_libraries(graphics
  graphicsmgr)
add_test(NAME graphics-test COMMAND graphics)
endif()
