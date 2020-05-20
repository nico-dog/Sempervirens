project(unittesting VERSION 1.0 LANGUAGES CXX)

# Define target
add_library(unittesting OBJECT)
target_sources(unittesting PRIVATE
  UnitTest.cpp
  UnitTestRegister.cpp)

target_precompile_headers(unittesting PRIVATE ../../include/Sempervirens_pch.hpp)

# Set target include directories
target_include_directories(unittesting PUBLIC ../../include)


# Set target compile options
target_compile_options(unittesting PRIVATE -Wall -O2 -fPIC)


# Set target compile features
target_compile_features(unittesting PRIVATE cxx_std_17)


# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(unittesting PRIVATE PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_testing})
target_compile_definitions(unittesting PRIVATE BUILD_UNITTESTING=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(unittesting PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(unittesting PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()


if(${build_unit_testing})

add_executable(register)
target_sources(register PRIVATE ../../tests/UnitTesting/UnitTestRegisterTest.cpp)
target_precompile_headers(register REUSE_FROM logger)
target_link_libraries(register PRIVATE unittesting logging)
target_compile_options(register PRIVATE -Wall -O2 -fPIC)
target_compile_features(register PRIVATE cxx_std_17)
target_compile_definitions(register PRIVATE BUILD_UNITTESTING=1)
if(${build_logging})
target_compile_definitions(register PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME register-test COMMAND register)

endif()
