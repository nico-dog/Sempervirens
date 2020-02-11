project(app VERSION 1.0 LANGUAGES CXX)

# Define target
add_library(app INTERFACE)
#target_sources(app PRIVATE)
target_include_directories(app INTERFACE include)

