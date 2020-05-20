project(memoryalloc VERSION 1.0 LANGUAGES CXX)

# Define target
add_library(memoryalloc OBJECT)
target_sources(memoryalloc PRIVATE
  MemoryArea.cpp
  MemoryAllocHeap.cpp
  LinearAllocator.cpp)

target_precompile_headers(memoryalloc PRIVATE ../../include/Sempervirens_pch.hpp)

# Set target include directories
target_include_directories(memoryalloc PUBLIC ../../include)


# Set target compile options
target_compile_options(memoryalloc PRIVATE -Wall -O2 -fPIC)


# Set target compile features
target_compile_features(memoryalloc PRIVATE cxx_std_17)


# Set target compile definitions
# platform macros (UNIX, WIN32, APPLE)
if(UNIX)
target_compile_definitions(memoryalloc PRIVATE PLATFORM_UNIX=1)
endif()

# build macros
if(${build_unit_testing})
target_compile_definitions(memoryalloc PRIVATE BUILD_UNITTESTING=1)
message(STATUS "Current build with unit testing")  
endif()
if(${build_logging})
target_compile_definitions(memoryalloc PRIVATE BUILD_LOGGING=1)
message(STATUS "Current build with logging")
endif()

# feature macros
if(${feature_thread_affinity})
target_compile_definitions(memoryalloc PRIVATE FEATURE_THREAD_AFFINITY=1)
endif()


if(${build_unit_testing})

add_executable(arena)
target_sources(arena PRIVATE ../../tests/MemoryAlloc/MemoryArenaTest.cpp)
target_precompile_headers(arena REUSE_FROM logger)
target_link_libraries(arena PRIVATE unittesting memoryalloc logging)
target_compile_options(arena PRIVATE -Wall -O2 -fPIC)
target_compile_features(arena PRIVATE cxx_std_17)
target_compile_definitions(arena PRIVATE BUILD_UNITTESTING=1)
if(${build_logging})
target_compile_definitions(arena PRIVATE BUILD_LOGGING=1)
endif()
add_test(NAME arena-test COMMAND arena)

endif()
