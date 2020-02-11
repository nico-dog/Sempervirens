project(renderer VERSION 1.0 LANGUAGES CXX)

#######################################################
#
# Define target for renderer manager static library
#
#######################################################
add_library(renderermgr STATIC)
target_sources(renderermgr PRIVATE
  src/RendererMgr/RendererMgr.cpp)
if(UNIX)
target_sources(renderermgr PRIVATE
  ../Core/src/DynamicLibs/DynamicLibs_unix.cpp
)
endif()

# Set target include directories
target_include_directories(renderermgr PUBLIC
  include
  ../Core/include
  ../Misc)

# Set target compile options, features and definitions
target_compile_options(renderermgr PRIVATE -Wall -O2)
target_compile_features(renderermgr PRIVATE cxx_std_17)
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(renderermgr PRIVATE PLATFORM_UNIX=1)
endif()
# build macros
if(${build_unit_testing})
target_compile_definitions(renderermgr PRIVATE BUILD_UNITTESTING=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(renderermgr PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()
# feature macros
if(${feature_thread_affinity})
target_compile_definitions(renderermgr PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()

# Link to imported targets
target_link_libraries(renderermgr PRIVATE
  ${CMAKE_DL_LIBS} # usually -ldl on unix platforms
  core)


#######################################################
#
# Define target for renderer shared library
#
#######################################################
add_library(oglrenderer SHARED)
target_sources(oglrenderer PRIVATE
  src/Renderer/IRenderer.cpp
  src/Renderer/OpenGLRenderer.cpp)

target_include_directories(oglrenderer PRIVATE
  include
  ../Imports/include
  ../Core/include)
  
# Set target compile options, features and definitions
target_compile_options(oglrenderer PRIVATE -Wall -O2)
target_compile_features(oglrenderer PRIVATE cxx_std_17)
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(oglrenderer PRIVATE PLATFORM_UNIX=1)  
endif()
# build macros
if(${build_unit_testing})
target_compile_definitions(oglrenderer PRIVATE BUILD_UNITTESTING=1)  
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(oglrenderer PRIVATE BUILD_LOGGING=1)  
message(STATUS "Current build with logging")
endif()
# feature macros
if(${feature_thread_affinity})
target_compile_definitions(oglrenderer PRIVATE FEATURE_THREAD_AFFINITY=1)  
endif()

# Link to imported targets
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(oglrenderer PRIVATE core glfw glad)


#######################################################
#
# Define test targets for CTest
#
#######################################################
if(${build_unit_testing})

add_executable(renderer)
target_sources(renderer PRIVATE test/RendererMgrTest.cpp)
target_link_libraries(renderer PRIVATE renderermgr)
target_compile_options(renderer PRIVATE -Wall -O2 -fPIC -g)
target_compile_features(renderer PRIVATE cxx_std_17)
target_compile_definitions(renderer PRIVATE BUILD_UNITTESTING=1)
if(UNIX)
target_compile_definitions(renderer PRIVATE PLATFORM_UNIX=1)
endif()
if(${build_logging})
target_compile_definitions(renderer PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME renderer-test COMMAND renderer)

endif()
