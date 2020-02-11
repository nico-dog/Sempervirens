project(imports VERSION 1.0 LANGUAGES C CXX)

add_library(glad STATIC)
target_sources(glad PRIVATE
  src/glad/glad.c)

target_include_directories(glad PUBLIC
  include)

target_compile_options(glad PRIVATE -Wall -O2 -fPIC)
