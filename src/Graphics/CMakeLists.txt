project(graphics VERSION 1.0 LANGUAGES CXX)

# Define targets
add_library(graphicsmgr STATIC)
target_sources(graphicsmgr PRIVATE
  src/GraphicsMgr/GraphicsMgr.cpp)
if(UNIX)
target_sources(graphicsmgr PRIVATE
  ../App/src/DynamicLibs/DynamicLibs_unix.cpp
)
endif()


# Set target include directories
target_include_directories(graphicsmgr PUBLIC
  include
  ../Utilities/include
  ../App/include)

add_library(graphicsogl SHARED)
target_sources(graphicsogl PRIVATE
  src/GraphicsRenderer/IGraphicsRenderer.cpp
  src/GraphicsRenderer/OpenGLRenderer.cpp)

target_include_directories(graphicsogl PRIVATE
  include
  ../Utilities/include
  ../App/include)
  

# Set target compile options
target_compile_options(graphicsmgr PRIVATE -Wall -O2)
  
target_compile_options(graphicsogl PRIVATE -Wall -O2)
  

# Set target compile features
target_compile_features(graphicsmgr PRIVATE cxx_std_17)

target_compile_features(graphicsogl PRIVATE cxx_std_17)
  

# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(graphicsmgr PRIVATE PLATFORM_UNIX=1)
target_compile_definitions(graphicsogl PRIVATE PLATFORM_UNIX=1)  
endif()

# build macros
if(${build_unit_tests})
target_compile_definitions(graphicsmgr PRIVATE BUILD_UNITTESTS=1)
target_compile_definitions(graphicsogl PRIVATE BUILD_UNITTESTS=1)  
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(graphicsmgr PRIVATE BUILD_LOGGING=1)
target_compile_definitions(graphicsogl PRIVATE BUILD_LOGGING=1)  
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(graphicsmgr PRIVATE FEATURE_THREAD_AFFINITY=1)
target_compile_definitions(graphicsogl PRIVATE FEATURE_THREAD_AFFINITY=1)  
endif()


# Link to imported targets
target_link_libraries(graphicsmgr PRIVATE
  ${CMAKE_DL_LIBS} # usually -ldl on unix platforms
  utilities)
  
target_link_libraries(graphicsogl PRIVATE utilities)


# Define tests for CTest
if(${build_unit_tests})

add_executable(graphics)
target_Sources(graphics PRIVATE test/GraphicsMgrTest.cpp)
target_link_libraries(graphics PRIVATE graphicsmgr)
target_compile_options(graphics PRIVATE -Wall -O2 -fPIC)
target_compile_features(graphics PRIVATE cxx_std_17)
target_compile_definitions(graphics PRIVATE BUILD_UNITTESTS=1)
if(UNIX)
target_compile_definitions(graphics PRIVATE PLATFORM_UNIX=1)
endif()
if(${build_logging})
target_compile_definitions(graphics PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME graphics-test COMMAND graphics)

endif()
