cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Sempervirens VERSION 1.0 LANGUAGES C CXX)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

include(GNUInstallDirs)

if(UNIX)
find_package(X11 REQUIRED)
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
endif()


# CTest
enable_testing()

# Project tree
add_subdirectory(Vendors)
add_subdirectory(Core)
add_subdirectory(Window)
#add_subdirectory(Input)
#add_subdirectory(Renderer)
add_subdirectory(Application)


# EXPORT
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:core> $<TARGET_OBJECTS:window> $<TARGET_OBJECTS:app>)

if(UNIX)
target_link_libraries(${PROJECT_NAME} INTERFACE X11::X11)
endif()

#set(CMAKE_INSTALL_PREFIX "/home/nico/Desktop/Test")

target_include_directories(${PROJECT_NAME} INTERFACE
  $<INSTALL_INTERFACE:include/${CMAKE_PROJECT_NAME}>)
  
export(TARGETS FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Targets.cmake)


file(WRITE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
  "include(CMakeFindDependencyMacro)\n"
  "if(UNIX)\n"
  "find_dependency(X11 REQUIRED)\n"
  "endif()\n"
  "include(${CMAKE_INSTALL_PREFIX}/lib/cmake/${CMAKE_PROJECT_NAME}/${CMAKE_PROJECT_NAME}Targets.cmake)\n")
  
install(FILES ${PROJECT_SOURCE_DIR}/Sempervirens.hpp
	DESTINATION include/${CMAKE_PROJECT_NAME})
install(FILES ${PROJECT_SOURCE_DIR}/Sempervirens_pch.hpp
        DESTINATION include/${CMAKE_PROJECT_NAME})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Application/include/Application
        DESTINATION include/${CMAKE_PROJECT_NAME})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Core/include/EventSystem
        DESTINATION include/${CMAKE_PROJECT_NAME})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Core/include/Logging
        DESTINATION include/${CMAKE_PROJECT_NAME})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Core/include/MemoryAlloc
        DESTINATION include/${CMAKE_PROJECT_NAME})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Window/include/Interface
        DESTINATION include/${CMAKE_PROJECT_NAME})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Window/include/Backend
        DESTINATION include/${CMAKE_PROJECT_NAME})	
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Misc/Macros
        DESTINATION include/${CMAKE_PROJECT_NAME})

install(FILES ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
        DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})

install(EXPORT ${CMAKE_PROJECT_NAME}Targets
        NAMESPACE Sempervirens::
        DESTINATION lib/cmake/${CMAKE_PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        EXPORT ${CMAKE_PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)	
