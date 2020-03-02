project(core VERSION 1.0 LANGUAGES CXX)

# Define target
add_library(window OBJECT)
if(UNIX)
target_sources(window PRIVATE
  src/Backend/Linux/LinuxWindow.cpp)
endif()

target_precompile_headers(window PRIVATE ../Sempervirens_pch.hpp)

# Set target include directories
target_include_directories(window PUBLIC
  include
  ../Input/include
  ../Core/include
  ../Misc)

# Set target compile options
target_compile_options(window PRIVATE -Wall -O2 -fPIC)

# Set target compile features
target_compile_features(window PRIVATE cxx_std_17)

# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(window PRIVATE PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_testing})
target_compile_definitions(window PRIVATE BUILD_UNITTESTING=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(window PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(window PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()




if(UNIX)
#find_package(X11 REQUIRED)
target_link_libraries(window PUBLIC X11::X11)
endif()




# Define tests
if(${build_unit_testing})

add_executable(app-window)
target_sources(app-window PRIVATE test/WindowTest.cpp)
target_precompile_headers(app-window PRIVATE ../Sempervirens_pch.hpp)
target_link_libraries(app-window PRIVATE window core)
target_compile_options(app-window PRIVATE -Wall -O2 -fPIC)
target_compile_features(app-window PRIVATE cxx_std_17)
target_compile_definitions(app-window PRIVATE BUILD_UNITTESTING=1)
if(${build_logging})
target_compile_definitions(app-window PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME app-window-test COMMAND app-window)

endif()
